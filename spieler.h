#ifndef SPIELER_H
#define SPIELER_H


class spieler
{
    public:
        spieler();
        virtual ~spieler();

        int anzahlgesetzteSteine =0;
        int anzahltatsaechlicheSteine=0;
        int anzahlmuehlen=0;
        int anzahlsteineweggenohmen=0;
        bool darfspringen=false;

    protected:

    private:
};

#endif // SPIELER_H
