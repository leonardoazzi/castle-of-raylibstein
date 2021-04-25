#include<raylib.h>

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
#define MAX_TIROS_DIR 3
#define MAX_TIROS_ESQ 3
#define SCREEN_WIDTH 800 //largura da tela
#define SCREEN_HEIGHT 300 //altura da tela
#define INIMIGOS 1

typedef struct Tiro
{
    Vector2 speed;
    bool active;
    Color color;
    Vector2 position;
    int lifeSpawn;
    float radius;
} Tiro;

typedef struct TiroEsq
{
    Vector2 speedEsq;
    bool activeEsq;
    Color colorEsq;
    Vector2 positionEsq;
    int lifeSpawnEsq;
    float radiusEsq;
} TiroEsq;

typedef struct Inimigo{
    Rectangle rec;
    bool active;
    Color color;

}Inimigo;

    static Tiro tiro[MAX_TIROS_DIR] = {0};
    static TiroEsq tiroEsq[MAX_TIROS_ESQ] = {0};
    static Inimigo inimigo[INIMIGOS] = {0};

int main()
{
    //Variaveis
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    bool direita;
    bool esquerda;

    int JogadorX = 400.0f; //posicao de spawn X do jogador
    int JogadorY = 200.0f; //posicao de spawn Y do jogador
    int moveX = 4; //velocidade de movimento do jogador no eixo x
    int moveY = 4; //velocidade de movimento do jogador no eixo x

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Castle os RaylibStein"); //inicializa a janela do jogo
    Vector2 position = {JogadorX, JogadorY}; //vetor posicao do jogador
    Texture2D Jogador = LoadTexture("Jogador.png"); //carrega o sprite do jogador

    Rectangle frameRec = {0.0f, 0.0f, (float)Jogador.width/5 , (float)Jogador.height};

    for (int i=0; i<MAX_TIROS_DIR; i++)
    {
        tiro[i].position = (Vector2){position.x+50, position.y+50};
        tiro[i].speed.x = 3;
        tiro[i].radius = 5;
        tiro[i].active = false;
        tiro[i].color = WHITE;
        tiro[i].lifeSpawn = 0;
    }

    for (int i=0; i<MAX_TIROS_ESQ; i++)
    {
        tiroEsq[i].positionEsq = (Vector2){position.x+20, position.y+20};
        tiroEsq[i].speedEsq.x = 3;
        tiroEsq[i].radiusEsq = 5;
        tiroEsq[i].activeEsq = false;
        tiroEsq[i].colorEsq = WHITE;
        tiroEsq[i].lifeSpawnEsq = 0;
    }

    for (int i = 0; i< INIMIGOS;i++)
    {
        inimigo[i].rec.width = 20;
        inimigo[i].rec.height = 40;
        inimigo[i].active = true;
        inimigo[i].color = RED;
    }

    SetTargetFPS(60); //seta para que o jogo rode a 60 frames

    while(!WindowShouldClose())
    {
        framesCounter++; //contador para mudar o sprite do jogador

        if(IsKeyDown(KEY_RIGHT)) //caso a seta da direita seja pressionada
        {
            position.x += moveX; //incrementa posicao x do jogador
            direita = true;
            esquerda = false;
            if (framesCounter>=60/framesSpeed)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 1) //faz o loop da animacao do jogador para a direita
                    currentFrame = 0;
                frameRec.x = (float)currentFrame*(float)Jogador.width/5;
            }
        }

        if(IsKeyDown(KEY_LEFT)) //caso a seta da esquerda seja pressionada
        {
            position.x -= moveX; //decrementa a posicao x do jogador
            direita = false;
            esquerda = true;
            if (framesCounter>=60/framesSpeed)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 3) //faz o loop da animacao do jogador para a esquerda
                    currentFrame = 2;
                frameRec.x = (float)currentFrame*(float)Jogador.width/5;
            }
        }

        if(IsKeyDown(KEY_UP)) //caso a seta de cima seja pressionada
        {
            position.y -= moveY;
            if (framesCounter>=60/framesSpeed)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 1) //faz o loop da animacao do jogador para cima
                    currentFrame = 0;
                frameRec.y = (float)currentFrame*(float)Jogador.height;
            }
        }

        if(IsKeyDown(KEY_DOWN)) //caso a seta de baixo seja pressionada
        {
            position.y += moveY;
            if (framesCounter>=60/framesSpeed)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 1) //faz o loop da animacao do jogador para baixo
                    currentFrame = 0;
                frameRec.y = (float)currentFrame*(float)Jogador.height;
            }
        }

        if(IsKeyPressed(KEY_SPACE) && esquerda)
        {
            for (int i = 0; i<MAX_TIROS_ESQ; i++)
            {
                if(!tiroEsq[i].activeEsq)
                {
                    tiroEsq[i].positionEsq = (Vector2){position.x+20, position.y+20};
                    tiroEsq[i].activeEsq = true;
                    break;
                }
            }
        }
        for (int i=0; i<MAX_TIROS_ESQ; i++)
        {
            if(tiroEsq[i].activeEsq)
            {
                tiroEsq[i].positionEsq.x -= 3;
                tiroEsq[i].lifeSpawnEsq++;
                if(tiroEsq[i].positionEsq.x <= -10)
                {
                    tiroEsq[i].activeEsq = false;
                }
                if (tiroEsq[i].activeEsq)
                {
                    DrawCircleV(tiroEsq[i].positionEsq, tiroEsq[i].radiusEsq, YELLOW);
                }
                if(tiroEsq[i].lifeSpawnEsq >=80)
                {
                    tiroEsq[i].positionEsq = (Vector2){position.x+20, position.y+20};
                    tiroEsq[i].speedEsq = (Vector2){0, 0};
                    tiroEsq[i].lifeSpawnEsq = 0;
                    tiroEsq[i].activeEsq = false;
                }
            }
        }

        if(IsKeyPressed(KEY_SPACE) && direita)
        {
            for (int i = 0; i<MAX_TIROS_DIR; i++)
            {
                if(!tiro[i].active)
                {
                    tiro[i].position = (Vector2){position.x+20, position.y+20};
                    tiro[i].active = true;
                    break;
                }
            }
        }
        for (int i=0; i<MAX_TIROS_DIR; i++)
        {
            if(tiro[i].active)
            {
                tiro[i].position.x += 3;
                tiro[i].lifeSpawn++;
                if(tiro[i].position.x > 800)
                {
                    tiro[i].active = false;
                }
                if (tiro[i].active)
                {
                    DrawCircleV(tiro[i].position, tiro[i].radius, YELLOW);
                }
                if(tiro[i].lifeSpawn >=80)
                {
                    tiro[i].position = (Vector2){position.x+20, position.y+20};
                    tiro[i].speed = (Vector2){0, 0};
                    tiro[i].lifeSpawn = 0;
                    tiro[i].active = false;
                }
            }
        }

        //setando a IA para os inimigos perseguirem o jogador
        for (int i = 0; i< INIMIGOS;i++)
        {
            if (position.x > inimigo[i].rec.x)
            {
                inimigo[i].rec.x += 2;
            }
            if (position.x < inimigo[i].rec.x)
            {
                inimigo[i].rec.x -= 2;
            }
            if (position.y > inimigo[i].rec.y)
            {
                inimigo[i].rec.y += 2;
            }
            if (position.y < inimigo[i].rec.y)
            {
                inimigo[i].rec.y -= 2;
            }
        }

        for (int i=0;i<MAX_TIROS_DIR;i++)
        {
            if((tiro[i].active))
            {
                for (int j=0; j < INIMIGOS;j++)
                {
                    if(inimigo[j].active && CheckCollisionCircleRec(tiro[i].position, tiro[i].radius, inimigo[j].rec))
                    {
                        tiro[i].active = false;
                        tiro[i].lifeSpawn = 0;
                        inimigo[j].active = false;
                    }
                }
            }
        }

        for (int i=0;i<MAX_TIROS_ESQ;i++)
        {
            if((tiroEsq[i].activeEsq))
            {
                for (int j=0; j < INIMIGOS;j++)
                {
                    if(inimigo[j].active && CheckCollisionCircleRec(tiroEsq[i].positionEsq, tiroEsq[i].radiusEsq, inimigo[j].rec))
                    {
                        tiroEsq[i].activeEsq = false;
                        tiroEsq[i].lifeSpawnEsq = 0;
                        inimigo[j].active = false;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE); //cor do fundo

        DrawTextureRec(Jogador, frameRec, position, WHITE); //desenha o jogador na tela

        for(int i=0; i<INIMIGOS;i++)
        {
            if(inimigo[i].active)
            {
                DrawRectangleRec(inimigo[i].rec, inimigo[i].color);
            }
        }

        EndDrawing();
    }

    UnloadTexture(Jogador); //da unload na textura do jogador

    CloseWindow();

    return 0;
}
