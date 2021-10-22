#include <iostream>

using namespace std;

struct RotorLayer
{
    int rotorNumber;
    bool notchRotate=false;
};

void rotate(RotorLayer** rotorUsed, int whichRotor, int numberOfLetters)
{
    int temp = rotorUsed[whichRotor][0].rotorNumber;
    bool temp2 = rotorUsed[whichRotor][0].notchRotate;
    for (int i = 0; i < numberOfLetters - 1; i++)
    {
        rotorUsed[whichRotor][i].rotorNumber = rotorUsed[whichRotor][i + 1].rotorNumber;
        rotorUsed[whichRotor][i].notchRotate = rotorUsed[whichRotor][i + 1].notchRotate;
    }
    rotorUsed[whichRotor][numberOfLetters - 1].rotorNumber = temp;
    rotorUsed[whichRotor][numberOfLetters - 1].notchRotate = temp2;
}

void rotateV2(RotorLayer** rotorUsed, int whichRotor, int numberOfLetters)
{
    int temp = rotorUsed[whichRotor][0].rotorNumber;
    for (int i = 0; i < numberOfLetters - 1; i++)
    {
        rotorUsed[whichRotor][i].rotorNumber = rotorUsed[whichRotor][i + 1].rotorNumber;
    }
    rotorUsed[whichRotor][numberOfLetters - 1].rotorNumber = temp;
}

void rotateBack(int** change, int whichRotor, int numberOfLetters)
{
    int temp = change[whichRotor][0];
    for (int i = 0; i < numberOfLetters - 1; i++)
    {
        change[whichRotor][i] = change[whichRotor][i + 1];
    }
    change[whichRotor][numberOfLetters - 1] = temp;
}






void transcriptThroughRotor(RotorLayer** rotorUsed, int numberOfLetters, int whichRotor, int place, int** change)
{
    for (int i = 0; i < numberOfLetters; i++)
    {
        int temp = i + rotorUsed[whichRotor - 1][i].rotorNumber;
        if (temp < 0)
        {
            temp = temp + (numberOfLetters);
        }
        else if (temp > (numberOfLetters - 1))
        {
            temp = temp % (numberOfLetters);
        }
        change[place - 1][temp] = (-1) * rotorUsed[whichRotor - 1][i].rotorNumber;
    }
}



void transcriptThroughRotorV2(RotorLayer** rotorUsed,  int numberOfLetters, int whichRotor,  int& thisValue)
{

    int temp = thisValue + rotorUsed[whichRotor - 1][thisValue].rotorNumber;
    if (temp < 0)
    {
        temp = temp + (numberOfLetters);
    }
    else if (temp > (numberOfLetters - 1))
    {
        temp = temp % (numberOfLetters);
    }
    thisValue = temp;


}


void transcriptThroughReflector(int** reflector,  int numberOfLetters, int whichReflectorUsed, int& thisValue)
{

    int temp = thisValue + reflector[whichReflectorUsed][thisValue];

    if (temp < 0)
    {
        temp = temp + (numberOfLetters);
    }
    else if (temp > (numberOfLetters - 1))
    {
        temp = temp % (numberOfLetters);
    }
    thisValue = temp;

}


void transcriptThroughRotorBack( int numberOfLetters, int whichRotor, int** change, int& thisValue)
{

    int temp = thisValue + change[whichRotor - 1][thisValue];
    if (temp < 0)
        temp = temp + numberOfLetters;
    if (temp > (numberOfLetters - 1))
        temp = temp % numberOfLetters;
    thisValue = temp;


}


int main()
{
    int numberOfLetters;
    int numberOfRotors;
    int numberOfReflectors;
    int numberOfInformations;
    int howManyRotorsUsed;
    int whichRotor;
    int whichReflectorUsed;
    int temp;
    int howFar;
    int thisValue = -1;






    cin >> numberOfLetters;
    cin >> numberOfRotors;

    RotorLayer** rotor = new RotorLayer * [numberOfRotors];

    for (int i = 0; i < numberOfRotors; i++)
    {

        rotor[i] = new RotorLayer[numberOfLetters];

        for (int j = 0; j < numberOfLetters; j++)
        {
            cin >> rotor[i][j].rotorNumber;
            rotor[i][j].rotorNumber = rotor[i][j].rotorNumber - j - 1;
        }

        cin >> temp;
        while (temp != 0)
        {
            cin >> howFar;
            rotor[i][howFar - 1].notchRotate = true;
            temp--;
        }

    }












    cin >> numberOfReflectors;
    int** reflector = new int* [numberOfReflectors];

    for (int i = 0; i < numberOfReflectors; i++)
    {

        reflector[i] = new int[numberOfLetters];

        for (int j = 0; j < numberOfLetters; j++)
        {
            cin >> reflector[i][j];
            reflector[i][j] = reflector[i][j] - j - 1;
        }
    }







    cin >> numberOfInformations;









    for (int i = 0; i < numberOfInformations; i++)
    {
        cin >> howManyRotorsUsed;
        RotorLayer** rotorUsed = new RotorLayer * [howManyRotorsUsed];
        int** change = new int* [howManyRotorsUsed];
        for (int z = 0; z < howManyRotorsUsed; z++)
        {
            cin >> whichRotor;
            rotorUsed[z] = new RotorLayer[numberOfLetters];
            change[z] = new int[numberOfLetters];
            for (int j = 0; j < numberOfLetters; j++)
            {
                if (z < 2) {
                    if (z == 1)
                    {
                        if (j == 0)
                        {
                            rotorUsed[z][numberOfLetters - 1].notchRotate = rotor[whichRotor][j].notchRotate;
                        }
                        else
                            rotorUsed[z][j - 1].notchRotate = rotor[whichRotor][j].notchRotate;
                        rotorUsed[z][j].rotorNumber = rotor[whichRotor][j].rotorNumber;
                    }
                    else
                    {
                        rotorUsed[z][j].rotorNumber = rotor[whichRotor][j].rotorNumber;
                        rotorUsed[z][j].notchRotate = rotor[whichRotor][j].notchRotate;
                    }
                }
                else
                    rotorUsed[z][j].rotorNumber = rotor[whichRotor][j].rotorNumber;
            }

            cin >> howFar;
            howFar =howFar -1;
            if (z < 2) {
                for (int p = 0; p < howFar; p++)
                {
                    rotate(rotorUsed, z, numberOfLetters);
                }
            }
            else
            {
                for (int p = 0; p < howFar; p++)
                {
                    rotateV2(rotorUsed, z, numberOfLetters);
                }
            }
        }

        cin >> whichReflectorUsed;

        int messageLetter;

        int ctr = 0, ctr1 = 0;
        int ifmove = 0;
        bool wait = 0;


        for (int p = 0; p < howManyRotorsUsed; p++)
        {
            transcriptThroughRotor(rotorUsed, numberOfLetters, p + 1, p + 1, change);
        }





        while (cin >> messageLetter && messageLetter != 0)
        {







            thisValue = messageLetter - 1;





            rotate(rotorUsed, 0, numberOfLetters);
            rotateBack(change, 0, numberOfLetters);

            if (wait == 1 && numberOfRotors > 2 && ifmove == 0) {
                rotate(rotorUsed, 1, numberOfLetters);
                rotateBack(change, 1, numberOfLetters);
                rotateV2(rotorUsed, 2, numberOfLetters);
                rotateBack(change, 2, numberOfLetters);
                ifmove = 1;
                wait = 0;
            }

            if (rotorUsed[0][0].notchRotate == true && howManyRotorsUsed > 1 && ctr != 0 && ifmove == 0)
            {
                rotate(rotorUsed, 1, numberOfLetters);
                rotateBack(change, 1, numberOfLetters);
                ctr1++;
            }


            if (howManyRotorsUsed > 2 && ctr1 != 0 && rotorUsed[1][0].notchRotate == true)
            {
                wait = 1;
            }

            ifmove = 0;
            ctr++;

            for (int p = 0; p < howManyRotorsUsed; p++)
            {
                transcriptThroughRotorV2(rotorUsed, numberOfLetters, p+1, thisValue);
            }

            transcriptThroughReflector(reflector, numberOfLetters, whichReflectorUsed, thisValue);

            for (int p = 0; p < howManyRotorsUsed; p++)
            {
                transcriptThroughRotorBack( numberOfLetters, howManyRotorsUsed - p,   change, thisValue);
            }



            cout << thisValue + 1 << " ";

        }
        for(int u=0;u<howManyRotorsUsed;u++)
            delete[] change[u];
        delete[] change;
    }

    delete[] rotor;
    delete[] reflector;

    return 0;
}