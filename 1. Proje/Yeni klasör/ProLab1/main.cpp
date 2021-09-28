#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
//koordinatlari tutar
struct point
{
    double x;
    double y;
} coordinats[100];
//cemberin capi ve merkezini tutar
struct circle
{
    struct point A;
    double r;
};
//iki nokta arasindaki uzaklik
double uzaklik(struct point p1, struct point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
//verilen noktanin cemberde olup olmadigina bakar
bool kapsar_mi(struct circle Circle, struct point p)
{
    return (uzaklik(Circle.A, p) <= Circle.r);

}
//cemberin merkezini xy cinsinden bulur
struct point merkezi_bul(double bx, double by, double cx, double cy)
{
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    struct point Center;
    Center.x = (cy * B - by * C) / (2 * D);
    Center.y = (bx * C - cx * B) / (2 * D);
    return Center;
}
//3 nokta cemberle kesisiyorsa
struct circle uc_kesen_cember(struct point p1, struct point p2, struct point p3)
{
    struct point P = merkezi_bul(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y);
    P.x += p1.x;
    P.y += p1.y;
    struct circle newCircle;
    newCircle.A = P;
    newCircle.r = uzaklik(P, p1);
    return newCircle;
}
//2 nokta cemberle kesisirse calİisir
struct circle iki_kesen_cember(struct point p1, struct point p2)
{
    struct point D;
    D.x = ((p1.x + p2.x) / 2.0);//cemberin x koordinati
    D.y = ((p1.y + p2.y) / 2.0);//cemberin y koordinati
    struct circle newCircle2;
    newCircle2.A = D;
    newCircle2.r = uzaklik(p1, p2) / 2.0;
    return newCircle2;
}
//pointlerin kapsayip kapsamamasina bakiyor
bool kapsayan_cember(struct circle C, struct point P[], int length)
{

    for (int i = 0; i < length; i++)
    {
        if (!kapsar_mi(C, P[i]))
        {
            return false;
        }

    }
    return true;
}
//ana fonksiyon buyuk cemberi kucultup en kucugunu buluyor.
struct circle minimum_enclosing_circle(struct point P[], int length)
{
    if (length == 0)
    {
        struct circle zero;
        zero.A.x = 0;
        zero.A.y = 0;
        zero.r = 0;
        return zero;
    }
    if (length == 1)
    {
        struct circle Circ;
        Circ.A.x = P[0].x;
        Circ.A.y = P[0].y;
        Circ.r = 0;
        return Circ;
    }

    double f = 9999999999999;
    struct circle mec;
    mec.A.x = 0;
    mec.A.y = 0;
    mec.r = f;
    //cemberi iki noktada kesisene kadar kuculten cember
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            struct circle tmp = iki_kesen_cember(P[i], P[j]);
            if (tmp.r < mec.r && kapsayan_cember(tmp, P, length))
            {
                mec = tmp;
            }

        }
    }
    //cemberi 3 noktada kesisene kadar kucultuyor.
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            for (int k = j + 1; k < length; k++)
            {
                struct circle tmp = uc_kesen_cember(P[i], P[j], P[k]);
                if (tmp.r < mec.r && kapsayan_cember(tmp, P, length))
                {
                    mec = tmp;
                }
            }
        }
    }
    return mec;
}
void koordinatciz()
{
    setcolor(WHITE);
    line(752, 0, 752, 864);
    line(320, 432, 1190, 432);
    line(320, 432, 330, 420);
    line(320, 432, 330, 442);
    line(1190, 432, 1180, 442);
    line(1190, 432, 1180, 420);
    line(752, 864, 745, 854);
    line(752, 864, 759, 854);
    line(752, 0, 745, 10);
    line(752, 0, 759, 10);
    for (int l = 1; l <= 20; l++)
    {
        line(747, 432 - (21 * l), 759, 432 - (21 * l));
        line(747, 432 + (21 * l), 759, 432 + (21 * l));
        line(773 - (21 * l), 426, 773 - (21 * l), 438);
        line(752 + (21 * l), 426, 752 + (21 * l), 438);
        if (l % 5 == 0)
        {
            line(765, 432 - (21 * l), 741, 432 - (21 * l));
            line(765, 432 + (21 * l), 741, 432 + (21 * l));
            line(752 - (21 * l), 420, 752 - (21 * l), 444);
            line(752 + (21 * l), 420, 752 + (21 * l), 444);
        }
    }


}
void cemberciz(float a, float b, float radius)
{


    setcolor(LIGHTMAGENTA);
    circle((a * 21) + 752, -(b * 21) + 432, (radius) * 21);

}
void cemberin_merkezi(float w, float q)
{

    setcolor(LIGHTBLUE);
    circle((w * 21) + 753, (q * 21) + 432, 5);
    floodfill((w * 21) + 753, (q * 21) + 432, LIGHTBLUE);

}


int main()
{
    FILE* myFile = fopen("points.txt", "r");
    if (myFile == NULL)
    {
        printf("The file does not exist.");
        exit(1);
    }
    printf("Dosyadan Okunan Noktalar:\n\n");
    int numbers[100];
    int a = 0, j = 0, z = 0;
    while (!feof(myFile))
    {
        fscanf(myFile, "%d", &numbers[a]);
        a++;
    }
    int b = a / 2;
    for (int i = 0; i < a; i += 2)

    {
        coordinats[j].x = numbers[i];
        j++;
    }
    for (int i = 1; i < a; i += 2)
    {
        coordinats[z].y = numbers[i];
        z++;
    }
    for (int i = 0; i < b; i++)
    {
        printf("%.2f %.2f\n", coordinats[i].x, coordinats[i].y);
    }
    fclose(myFile);
    int length1 = a / 2;
    struct circle C1;
    printf("\nCemberin Koordinatlari Ve Yaricapi:\n");
    C1 = minimum_enclosing_circle(coordinats, length1);
    printf("\nx = %.2f  y= %.2f  r= %.2f \n", C1.A.x, C1.A.y, C1.r);
    initwindow(1366, 900, "PROLABPROJE1");
    int noktalar[b - 1][2];
    for (int i = 1; i <= b; i++) {
        noktalar[i][1] = coordinats[i - 1].x;
        noktalar[i][2] = coordinats[i - 1].y;
    }
    for (int l = 1; l <= b; l++)
    {
        setcolor(LIGHTBLUE);
        circle((noktalar[l][1] * 21) + 752, -(noktalar[l][2] * 21) + 432, 5);
        floodfill((noktalar[l][1] * 21) + 752, -(noktalar[l][2] * 21) + 432, LIGHTBLUE);
    }

    for (int l = 1; l <= b; l++)
    {

        setcolor(LIGHTBLUE);
        line((noktalar[l][1] * 21) + 752, -(noktalar[l][2] * 21) + 432, (noktalar[l + 1][1] * 21) + 752, -(noktalar[l + 1][2] * 21) + 432);
    }

    koordinatciz();
    cemberciz(C1.A.x, C1.A.y, C1.r);
    cemberin_merkezi(C1.A.x, -C1.A.y);
    while (!kbhit());
    closegraph();
    getch();
    return 0;
}
