#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
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
    int peonDobleAvanceFila;
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
int esPiezadeJugador(Partida *p,int f,int c,int turno);

void main(void)
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
    }

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
        p->peonDobleAvanceFila=-1;
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
        fgets(entrada,sizeof(entrada),stdin);

        entrada[strcspn(entrada,"\n")]=0;
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
        }
        int esPiezadeJugador(Partida *p, int f,int c,int turno)
        {
            char pieza=p->tablero[f][c];
            if(pieza==VACIO)
                return FALSO;
            return(turno == BLANCAS)? isupper(pieza) :islower(pieza);
        }
        int MovimientoDejaEnJaque(Partida *p,Movimiento mov)
        {
            char tableroTemp[8][8];
            int i,j;
            int enJaque;

            for(i=0;i<FILAS;i++)
            {
                for(j=0;j<COLUMNAS;j++)
                {
                    tableroTemp[i][j]=p->tablero[i][j];
                }
            }
            tableroTemp[mov.fDestino][mov.cDestino]=tableroTemp[mov.fOrigen]
            [mov.cOrigen];
            tableroTemp[mov.fOrigen][mov.cOrigen]=VACIO;

            enJaque= estaEnJaque(p->turnoActual,tableroTemp);
            return enJaque;
        }
        int esMovLegal(Partida *p,Movimiento mov)
        {
            if(!esPiezadeJugador(p,mov.fOrigen,mov.cOrigen,p->turnoActual))
                return FALSO;
            if(esPiezadeJugador(p,mov.fDestino,mov.cDestino,p->turnoActual))
                return FALSO;

            if(MovimientoDejaEnJaque(p,mov))
                return FALSO;

            return VERDADERO;
        }
        void hacerMovimiento(Partida *p,Movimiento mov)
        {
            char pieza=p->tablero[mov.fOrigen][mov.cOrigen];

            p->tablero[mov.fDestino][mov.cDestino]=pieza;
            p->tablero[mov.fOrigen][mov.cOrigen]=VACIO;

            if(pieza == REY_B)
                p->reyBlancoMovido=VERDADERO;
            if(pieza == REY_N)
                p->reyNegroMovido=VERDADERO;
            if(mov.fOrigen==7 && mov.cOrigen==0)
                p->torreBlancaIzqMovida=VERDADERO;
            if(mov.fOrigen==7 && mov.cOrigen==7)
           {p->torreBlancaDerMovida=VERDADERO;}
            if(mov.fOrigen==0 && mov.cOrigen==0)
                p->torreNegraIzqMovida=VERDADERO;
            if(mov.fOrigen==0 && mov.cOrigen==7)
                p->torreNegraDerMovida=VERDADERO;
        }

        void CambiarTurno(Partida *p)
        {
            p->turnoActual=(p->turnoActual ==BLANCAS)? NEGRAS : BLANCAS;
        }
        int estaEnJaque(int colorRey,char tableroTemp[8][8])
        {
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
                    if(esPiezadeJugador(p,fO,cO,p->turnoActual))
                    {
                        for(fD=0;fD<FILAS;fD++)
                            {
                                for(cD=0;cD<COLUMNAS;cD++)
                                {
                                    mov.fOrigen=fO;
                                    mov.cOrigen=cO;
                                    mov.fDestino=fD;
                                    mov.cDestino=cD;
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








