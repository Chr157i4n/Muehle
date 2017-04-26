#ifndef SPIELFELD_H
#define SPIELFELD_H


class spielfeld
{
    public:
        spielfeld();
        virtual ~spielfeld();

        int wert;
        bool istInEinerMuehle=false;

        int muehlenPaar1X=0,muehlenPaar1Y=0,muehlenPaar2X=0,muehlenPaar2Y=0;
    protected:

    private:
};

#endif // SPIELFELD_H
