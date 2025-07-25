#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int FILAS=8;
const int COLUMNAS=8;

const char PEON_B='P';
const char CABALLO_B='N';
const char ALFIL_B='B';
const char TORRE_B='R';
const char REINA_B='Q';
const char REY_B='K';
const char PEON_N='p';
const char CABALLO_N='n';
const char ALFIL_N='b';
const char TORRE_N='r';
const char REINA_N='q';
const char REY_N='k';
const char VACIO=' ';

const int BLANCAS=0;
const int NEGRAS=1;
const int FALSO=0;
const int VERDADERO=1;

typedef struct
{
    int fOrigen,cOrigen,fDestino,cDestino;
}Movimiento;

//Estado de la Partida//

typedef struct
{
    char tablero[8][8];
    int turnoActual;
    int reyBlancoMovido;
    int reyNegroMovido;
    int torreBlancaIzqMovida;
    int torreBlancaDerMovida;
    int torreNegraIzqMovida;
    int torreNegraDerMovida;
    int peonDobleAvanceCol;
}Partida;

void iniciaPartida(Partida *p);
void muestraTablero(Partida *p);
int obtenMovimientoUsuario(Movimiento *mov, Partida *partida);
int esMovLegal(Partida *p,Movimiento mov);
void hacerMovimiento(Partida *p,Movimiento mov);
void CambiarTurno(Partida *p);
int estaEnJaque(int colorRey,char tableroTemp[8][8]);
int existeMovLegal(Partida *p);
int esJaqueMate(Partida *p);
int esAhogado(Partida *p);

int validMovPeon(Partida *p,Movimiento mov);
int validMovLineal(char tablero[8][8],Movimiento mov);
int validMovDiagonal(char tablero[8][8],Movimiento mov);
int validMovCaballo(Movimiento mov);
int validMovRey(Partida *p,Movimiento mov);

int esPiezadeJugador(char pieza,int turno);
int esContrincante(char pieza,int turno);
void PromPeon(Partida *p,int f,int c);

int main(void)
{
    Partida partida;
    Movimiento mov;
    int findePartida=FALSO;
    iniciaPartida(&partida);
    while(!findePartida)
    {
        muestraTablero(&partida);
        if(estaEnJaque(partida.turnoActual,partida.tablero))
        {
            printf("El rey %s esta en jaque.\n",(partida.turnoActual== BLANCAS)? "BLANCO" : "NEGRO");
        }
        if(esJaqueMate(&partida))
        {
            printf("JAQUE MATE.Ganan las %s.\n",(partida.turnoActual ==BLANCAS)?"Negras" : "Blancas");
            findePartida=VERDADERO;
        }
        else if (esAhogado(&partida))
        {
            printf("Empate por ahogado.\n");
            findePartida=VERDADERO;
        }
        if(!findePartida)
            {
                if(obtenMovimientoUsuario(&mov,&partida))
                {
                    if(esMovLegal(&partida,mov))
                    {
                        hacerMovimiento(&partida,mov);
                        CambiarTurno(&partida);
                    }
                    else
                    {
                        printf("\nError: Movimiento ilegal.Intente de nuevo.\n");
                    }
                }
                else
                {
                    printf("\nError en la entrada.Formato: a2 a4.Intente de nuevo.\n");
                }

            }
        }

//Coloca las piezas en su posicion inicial//
    void iniciaPartida(Partida *p)
    {
        char piezasNegras[8]={'r','n','b','q','k','b','n','r'};
        char piezasBlancas[8]={'R','N','B','Q','K','B','N','R'};
        int i,j;

        for (j=0;j<COLUMNAS;j++)
        {
            p->tablero[0][j]=piezasNegras[j];
            p->tablero[1][j]=PEON_N;
            p->tablero[6][j]=PEON_B;
            p->tablero[7][j]=piezasBlancas[j];
        }
        //Llena el centro del tablero con espacios vacios//
        for(i=2;i<6;i++)
        {
            for(j=0;j<COLUMNAS;j++)
            {
                p->tablero[i][j]=VACIO;
            }
        }
        p->turnoActual=BLANCAS;
        p->reyBlancoMovido=FALSO;
        p->reyNegroMovido=FALSO;
        p->torreBlancaIzqMovida=FALSO;
        p->torreBlancaDerMovida=FALSO;
        p->torreNegraIzqMovida=FALSO;
        p->torreNegraDerMovida=FALSO;
        p->peonDobleAvanceCol=-1;
    }
    void muestraTablero(Partida *p)
    {
        int i,j;
        printf("\n   a b c d e f g h \n ------------------\n");
        for(i=0;i<FILAS;i++)
        {
            printf("%d| ",8-i);
            for(j=0;j<COLUMNAS;j++)
            {
                printf("%c ",p->tablero[i][j]);
            }
            printf("| %d\n",8-i);

    }
    printf("  ------------------\n  a b c d e f g h\n\n");
    }
    int obtenMovimientoUsuario(Movimiento *mov,Partida *partida)
    {
        char entrada[10];
        int fOrigen,cOrigen,fDestino,cDestino;

        printf("Turno de la %s. Ingrese movimiento (tipo:e2 e3):",
        (partida->turnoActual==BLANCAS)? "Blancas" : "Negras");
        fgets(entrada, sizeof(entrada),stdin);

        if(strlen(entrada)<5)
            return FALSO;
        cOrigen=tolower(entrada[0]) -'a';
        fOrigen=8-(entrada[1]-'0');
        cDestino=tolower(entrada[3])-'a';
        fDestino=8-(entrada[4]-'0');

        if(fOrigen <0 || fOrigen >=FILAS ||cOrigen <0 || cOrigen >=COLUMNAS ||
           fDestino <0 || fDestino >=FILAS || cDestino <0 || cDestino >=COLUMNAS)
        {
            return FALSO;
        }
        mov->fOrigen=fOrigen;
        mov->cOrigen=cOrigen;
        mov->fDestino=fDestino;
        mov->cDestino=cDestino;

        return VERDADERO;
        }//Verifica si una celda pertenece al jugador actual//
        int esPiezadeJugador(char pieza,int turno)
        {
            if(pieza==VACIO)
                return FALSO;
            return(turno == BLANCAS)? isupper(pieza) :islower(pieza);
        }
        int esContrincante(char pieza,int turno)
        {
           if(pieza==VACIO) return FALSO;
           return (turno == BLANCAS)?islower(pieza): isupper(pieza);
        }
        int validMovLineal(char tablero[8][8],Movimiento mov)
        {
            int PasoF =(mov.fDestino > mov.fOrigen)?1 : (mov.fDestino <mov.fOrigen)?-1:0;
            int PasoC=(mov.cDestino>mov.cOrigen)? 1: (mov.cDestino >mov.cOrigen)? -1 :0;
            int f=mov.fOrigen + PasoF;
            int c=mov.cOrigen +PasoC;

            while(f !=mov.fDestino || c !=mov.cDestino)
            {
                if(tablero[f][c]!=VACIO)return FALSO;
                f +=PasoF;
                c+=PasoC;
            }
            return VERDADERO;
        }
        int validMovDiagonal(char tablero[8][8],Movimiento mov)
        {
            int PasoF=(mov.fDestino>mov.fOrigen)?1: -1;
            int PasoC=(mov.cDestino>mov.cOrigen)?1: -1;

            int f=mov.fOrigen +PasoF;
            int c=mov.cOrigen +PasoC;
            while(f !=mov.fDestino)
            {
                if(tablero[f][c] !=VACIO)return FALSO;
                f+= PasoF;
                c+= PasoC;
            }
            return VERDADERO;
            }
            int validMovPeon(Partida *p,Movimiento mov)
            { int dir=(p->turnoActual ==BLANCAS)?-1 : 1;
            int fO=mov.fOrigen,cO=mov.cOrigen,fD=mov.fDestino,cD=mov.cDestino;

            if(fD == fO + dir && cD ==cO && p->tablero[fD][cD] ==VACIO)return VERDADERO;

             int fInicial=(p->turnoActual ==BLANCAS)  ?6 :1;
             if(fO ==fInicial && fD == fO +2 * dir && cD == cO && p->tablero[fO + dir][cD]==VACIO && p->tablero[fD][cD]==VACIO)
                return VERDADERO;

             if(fD==fO+dir &&(cD == cO +1 || cD==cO -1) && esContrincante(p->tablero[fD][cD],p->turnoActual))return VERDADERO;
             return FALSO;
             }
             int validMovCaballo(Movimiento mov)
             {int df=abs(mov.fDestino - mov.fOrigen);
             int dc=abs(mov.cDestino-mov.cOrigen);
             return(df ==2 && dc ==1)||(df==1 && dc ==2);
             }
             int validMovRey(Partida *p,Movimiento mov)
             {
                 int df=abs(mov.fDestino- mov.fOrigen);
                 int dc=abs(mov.cDestino-mov.cOrigen);

                 if(df <= 1 && dc<=1)return VERDADERO;

                 int filaRey=(p->turnoActual == BLANCAS)? 7:0;
                 if(mov.fOrigen !=filaRey || mov.cOrigen !=4) return FALSO;

                 if(estaEnJaque(p->turnoActual,p->tablero))return FALSO;

                 if(mov.cDestino == 6 && dc ==2)
                 {
                     int reyMovido=(p->turnoActual==BLANCAS)? p->reyBlancoMovido : p->reyNegroMovido;
                     int torreMovida=(p->turnoActual==BLANCAS)?p->torreBlancaDerMovida: p->torreNegraDerMovida;
                     if (reyMovido || torreMovida)return FALSO;

                     if(p->tablero[filaRey][5]==VACIO && p->tablero[filaRey][6]==VACIO)
                     {
                         char tempTablero[FILAS][COLUMNAS];
                         memcpy(tempTablero,p->tablero,sizeof(p->tablero));

                         tempTablero[filaRey][5]=tempTablero[filaRey][4];
                         tempTablero[filaRey][4]=VACIO;
                         if(estaEnJaque(p->turnoActual,tempTablero))return FALSO;
                         return VERDADERO;
                     }
                 }
                 else if(mov.cDestino ==2 && dc ==2)
                 {
                     int reyMovido=(p->turnoActual==BLANCAS)? p->reyBlancoMovido :p->reyNegroMovido;
                     int torreMovida=(p->turnoActual==BLANCAS)?p->torreBlancaIzqMovida :p->torreNegraIzqMovida;
                     if (reyMovido || torreMovida) return FALSO;

                     if(p->tablero[filaRey][1]==VACIO && p->tablero[filaRey][2]==VACIO && p->tablero[filaRey][3]==VACIO)
                     {
                         char tempTablero[FILAS][COLUMNAS];
                         memcpy(tempTablero,p->tablero,sizeof(p->tablero));

                         tempTablero[filaRey][3]=tempTablero[filaRey][4];
                         tempTablero[filaRey][4]=VACIO;
                         if(estaEnJaque(p->turnoActual,tempTablero))return FALSO;

                          return VERDADERO;
                     }
                 }
                 return FALSO;
                }
                int esMovLegal(Partida *p,Movimiento mov)
                {
                    char pieza,piezaDestino;
                    int esLegal=FALSO;

                    if(!esPiezadeJugador(p->tablero[mov.fOrigen][mov.cOrigen],p->turnoActual))return FALSO;
                    if(esPiezadeJugador(p->tablero[mov.fDestino][mov.cDestino],p->turnoActual))return FALSO;

                    pieza= tolower (p->tablero[mov.fOrigen][mov.cOrigen]);

                    switch(pieza)
                    {
                        case 'p':esLegal=validMovPeon(p,mov);break;
                        case 'r':esLegal=(mov.fOrigen ==mov.fDestino || mov.cOrigen == mov.cDestino)&& validMovLineal(p->tablero,mov);break;
                        case 'n':esLegal=validMovCaballo(mov);break;
                        case 'b':esLegal=abs(mov.fDestino-mov.fOrigen)==abs(mov.cDestino -mov.cOrigen) && validMovDiagonal(p->tablero,mov);break;
                        case 'q':esLegal=(mov.fOrigen ==mov.fDestino ||mov.cOrigen ==mov.cDestino || abs(mov.fDestino-mov.fOrigen)==abs(mov.cDestino-mov.cOrigen))&& (validMovLineal(p->tablero,mov)||validMovDiagonal(p->tablero,mov));break;
                        case 'k':esLegal=validMovRey(p,mov);break;
                        default: esLegal=FALSO;break;
                    }
                    if(!esLegal)return FALSO;

                    Partida partidatemp=*p;

                    char piezaMovidaTemp=partidatemp.tablero[mov.fOrigen][mov.cOrigen];
                    partidatemp.tablero[mov.fDestino][mov.cDestino]=piezaMovidaTemp;
                    partidatemp.tablero [mov.fOrigen][mov.cOrigen]=VACIO;

                    if(tolower(piezaMovidaTemp)=='p')
                    {int filaalpaso=(p->turnoActual==BLANCAS)? 3:4;
                    if(mov.fOrigen == filaalpaso && p->peonDobleAvanceCol ==mov.cDestino && abs(mov.cDestino -mov.cOrigen)==1 && abs(mov.fDestino-mov.fOrigen)==1 && partidatemp.tablero[mov.fDestino -(p->turnoActual ==BLANCAS? -1 : 1)][mov.cDestino]==((p->turnoActual ==BLANCAS)? PEON_N : PEON_B))
                    { partidatemp.tablero[mov.fDestino -(p->turnoActual== BLANCAS?-1 : 1)][mov.cDestino]=VACIO;
                    }
                }
                if(tolower(piezaMovidaTemp)=='k' && abs(mov.cDestino-mov.cOrigen)==2)
                {int fila=mov.fOrigen;
                int colTorreOrigen=(mov.cDestino ==6)? 7: 0;
                int colTorreDestino=(mov.cDestino==6)?5 :3;
                partidatemp.tablero[fila][colTorreDestino]=partidatemp.tablero[fila][colTorreOrigen];
                partidatemp.tablero[fila][colTorreOrigen]=VACIO;
                }

                if(estaEnJaque(p->turnoActual,partidatemp.tablero))return FALSO;
                return VERDADERO;
                }

                void hacerMovimiento(Partida *p, Movimiento mov)
                {
                    char pieza=p->tablero[mov.fOrigen][mov.cOrigen];
                    int fO=mov.fOrigen,cO=mov.cOrigen,fD=mov.fDestino,cD=mov.cDestino;

                    p->peonDobleAvanceCol=-1;

                    if(tolower(pieza)=='p')
                    {if(abs(fD-fO)==2) {p->peonDobleAvanceCol=cO;
                    }else{

                    int filaalpaso=(p->turnoActual==BLANCAS)? 3: 4;
                    if(fO== filaalpaso && cD==p->peonDobleAvanceCol && abs(cD-cO) ==1 && abs(fD-fO)==1 && p->tablero[fD- ((p->turnoActual==BLANCAS)?-1 : 1)[cD]==((p->turnoActual==BLANCAS)? PEON_N : PEON_B))
                    {p->tablero[fD-((p->turnoActual==BLANCAS)?-1:1)][cD]=VACIO;

                    }
                    }
                        p->tablero[fO][cD]=VACIO;
                    }
                }
                if(tolower(pieza)=='k' && abs(cD-cO)==2)
                {
                    int fila=fO;
                    int colTorreOrigen,colTorreDestino;

                    if(cD==6)
                    {
                        colTorreOrigen=7;
                        colTorreDestino=5;
                    }else{
                    colTorreOrigen=0;
                    colTorreDestino=3;
                    }
                    p->tablero[fila][colTorreDestino]=p->tablero[fila][colTorreOrigen];
                    p->tablero[fila][colTorreOrigen]=VACIO;
                }
                p->tablero[fD][cD]=pieza;
                p->tablero[fO][cO]=VACIO;

                if(pieza ==REY_B)p->reyBlancoMovido=VERDADERO;
                if(pieza ==REY_N)p->reyNegroMovido=VERDADERO;
                if(fO==7 && cO ==0)p->torreBlancaIzqMovida=VERDADERO;
                if(fO==7 && cO==7) p->torreBlancaDerMovida=VERDADERO;
                if(fO==0 && cO==0) p->torreNegraIzqMovida=VERDADERO;
                if(fO==0 && cO==7) p->torreNegraDerMovida=VERDADERO;

                if(tolower(pieza)=='p' && (fD==0 || fD==7))
                {
                    PromPeon(p,fD,cD);
                }

            void CambiarTurno(Partida *p)
        {
            p->turnoActual=(p->turnoActual ==BLANCAS)? NEGRAS : BLANCAS;
        }
        int estaEnJaque(int colorRey,char tablero[8][8])
        {
            int fR=-1,cR=-1,i,j,f,c;
            char reyBuscado=(colorRey==BLANCAS)?REY_B :REY_N;

            for(i=0;i<FILAS;i++)
            {
                for(j=0;j<COLUMNAS;j++)
                {
                    if(tablero[i][j]==reyBuscado)
                    {
                        fR=i;
                        cR=j;
                        break;
                    }
                }
                if(fR !=-1)break;
            }
            if(fR ==-1)return FALSO;

            int dir=(colorRey==BLANCAS)?-1:1;
            char peonCon=(colorRey==BLANCAS)?PEON_N : PEON_B;

            if(fR + dir >=0 && fR + dir <FILAS)
            {
                if(cR >0 && tablero[fR + dir][cR-1]== peonCon)return VERDADERO;
                if(cR <7 && tablero[fR + dir][cR +1]==peonCon)return VERDADERO;
            }
            int movsCaballo[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,-2},{1,-2},{1,2},{2,-1},{2,1}};
            char caballoCon=(colorRey == BLANCAS)?CABALLO_N : CABALLO_B;
            for (i=0;i<8;i++)
            {
                f=fR+movsCaballo[i][0];
                c=cR + movsCaballo[i][1];
                if(f>=0 && f<FILAS && c >=0 && c<COLUMNAS && tablero[f][c]==caballoCon) return VERDADERO;
                }
                int dirs[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
                for(i=0;i<8;i++)
                {
                    for(j=1;j<8;j++)
                    {
                        f=fR +j *dirs[i][0];
                        c=cR +j *dirs[i][1];
                        if(f<0 ||f>=FILAS ||c<0 ||c>=COLUMNAS)break;

                        if(tablero[f][c] !=VACIO)
                        {
                            if(esContrincante(tablero[f][c],colorRey))
                            {
                                char piezaEncon=tolower(tablero[f][c]);
                                if(i<4 && (piezaEncon== 'r' || piezaEncon== 'q'))return VERDADERO;
                                if(i>=4 &&(piezaEncon=='b' || piezaEncon=='q'))return VERDADERO;
                                if(piezaEncon == 'k' && j==1)return VERDADERO;
                            }
                            break;
                            }
                          }
                        }
                        return FALSO;
        }
        int existeMovLegal(Partida *p)
        {
            Movimiento mov;
            int fO,cO,fD,cD;

            for(fO=0;fO<FILAS;fO++)
            {
                for(cO=0;cO<COLUMNAS;cO++)
                {
                    if(esPiezadeJugador(p->tablero[fO][cO],p->turnoActual))
                    {
                        for(fD=0;fD<FILAS;fD++)
                        {
                            for(cD=0;cD<COLUMNAS;cD++)
                            {
                                mov.fOrigen=fO;
                                mov.cOrigen=cO;
                                mov.fDestino=fD;
                                mov.fOrigen=cD;
                                if(esMovLegal(p,mov))
                                {
                                    return VERDADERO;
                                }
                            }
                        }
                    }
                }
            }
            return FALSO;
        }
        int esJaqueMate(Partida *p)
        {
            return estaEnJaque(p->turnoActual,p->tablero) && !existeMovLegal(p);
        }
        int esAhogado(Partida *p)
        {
            return !estaEnJaque(p->turnoActual,p->tablero)&& !existeMovLegal(p);
        }
        void PromPeon(Partida *p,int f, int c)
        {
            char eleccion;
            char nuevaPieza=REINA_B;

            printf("Promocion de Peon.Elige (Q,R,B,N):");
            eleccion= getchar();
            fflush(stdin);

            switch(toupper(eleccion))
            {
                case 'R':nuevaPieza=TORRE_B;break;
                case 'B':nuevaPieza=ALFIL_B;break;
                case 'N':nuevaPieza=CABALLO_B;break;
            }
            p->tablero[f][c]=(p->turnoActual == BLANCAS)? nuevaPieza : tolower(nuevaPieza);
     }
     return 0;
     }





