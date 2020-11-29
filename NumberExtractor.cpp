#include "NumberExtractor.h"
#include <iostream>
#include <sstream>
#include "map"
NumberExtractor::NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter)
{
    std::map<std::string, int> conv;
    conv["zero"] = 0;
    conv["one"] = 1;
    conv["two"] = 2;
    conv["three"] = 3;
    conv["four"] = 4;
    conv["five"] = 5;
    conv["six"] = 6;
    conv["seven"] = 7;
    conv["eight"] = 8;
    conv["nine"] = 9;
    conv["ten"] = 10;

    conv["eleven"] = 11;
    conv["twelve"] = 12;
    conv["thirteen"] = 13;
    conv["fourteen"] = 14;
    conv["fifteen"] = 15;
    conv["sixteen"] = 16;
    conv["seventeen"] = 17;
    conv["eighteen"] = 18;
    conv["ninteen"] = 19;

    conv["thousand"] = 1000;
    conv["hundred"] = 100;

    conv["twenty"] = 20;
    conv["thirty"] = 30;
    conv["forty"] = 40;
    conv["fifty"] = 50;
    conv["sixty"] = 60;
    conv["seventy"] = 70;
    conv["eighty"] = 80;
    conv["ninety"] = 90;

    std::vector<int> numsExtracted;
    std::istringstream iss(astr_WordSeq);
    std::string word;
    int number;
    while (iss >> word)
    {
        /* do stuff with word */
        bool hasEndTy = false;
        if (IfWordIsNumber(conv, word))
        {
            number = conv[word];
            if (EndsWith(word, "ty"))
            {
                numsExtracted.push_back(number / 10);
                numsExtracted.push_back(10);
                hasEndTy = true;
                continue;
            }
            if (!hasEndTy)
            {
                numsExtracted.push_back(number);
            }
            hasEndTy = false;
        }
        else
        {
            numsExtracted.push_back(333);
        }
    }
    int out = 0;
    // for (int i = 0; i < numsExtracted.size(); i++)
    // {
    //     std::cout << numsExtracted[i] << " ;";
    // }
    for (int i = 0; i < numsExtracted.size(); i++)
    {
        out = numsExtracted[i];
        if (out == 0)
        {
            continue;
        }
        if (out != 333)
        {
            // if next is 1000
            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
            {
                out = out * 1000;
                i++;
                // if next is 0
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                {
                    out = out * 10;
                    i++;
                }
                // if next is 100
                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                {
                    out = out + numsExtracted[i + 1] * 100;
                    i++;
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    //if next is 10
                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                    {
                        out = out + numsExtracted[i + 1] * 10;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next 2 is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + +numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // if next is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                }

                //if next is 10
                else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                {
                    out = out + numsExtracted[i + 1] * 10;
                    i++;
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    // if next is 100
                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                    {
                        out = out + numsExtracted[i + 1] * 100;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        //if next is 10
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                    }

                    // if next 2 is <10
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                    {
                        out = out + +numsExtracted[i + 1];
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                    }
                }
                // if next is <10
                else
                {
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                    {
                        out = out + numsExtracted[i + 1];
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                    }
                }
            }

            // if next is 100
            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 100)
            {
                out = out * 100;
                i++;
                // if next is 1000
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                {
                    out = out * 1000;
                    i++;
                    // if next is 100
                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                    {
                        out = out + numsExtracted[i + 1] * 100;
                        i++;
                        i++;
                        //if next is 10
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                            }
                        }
                    }

                    //if next is 10
                    else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                    {
                        out = out + numsExtracted[i + 1] * 10;
                        i++;
                        i++;
                        // if next 2 is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                        {
                            out = out + +numsExtracted[i + 1];
                            i++;
                        }
                    }
                    else
                    {
                        // if next is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + numsExtracted[i + 1];
                            i++;
                        }
                    }
                }

                //if next is 10
                else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                {
                    out = out + numsExtracted[i + 1] * 10;
                    i++;
                    i++;
                    // if next is 1000
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                    {
                        out = out * 1000;
                        i++;
                        // if next is 100
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                        {
                            out = out + numsExtracted[i + 1] * 100;
                            i++;
                            i++;
                            //if next is 10
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                }
                            }
                        }

                        //if next is 10
                        else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 100
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                            {
                                out = out + numsExtracted[i + 1] * 100;
                                i++;
                                i++;
                                //if next is 10
                                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                                {
                                    out = out + numsExtracted[i + 1] * 10;
                                    i++;
                                    i++;
                                    // if next 2 is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + +numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                                else
                                {
                                    // if next is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                            }

                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                            }
                        }
                        // if next is <10
                        else
                        {
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                            }
                        }
                    }

                    // if next is <10
                    else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                    {
                        out = out + numsExtracted[i + 1];
                        i++;
                    }
                    else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] == 1000)
                    {
                        out = out + numsExtracted[i + 1];
                        i++;
                        // if next is 1000
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                        {
                            out = out * 1000;
                            i++;
                            // if next is 100
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                            {
                                out = out + numsExtracted[i + 1] * 100;
                                i++;
                                i++;
                                //if next is 10
                                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                                {
                                    out = out + numsExtracted[i + 1] * 10;
                                    i++;
                                    i++;
                                    // if next 2 is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + +numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                                else
                                {
                                    // if next is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                            }

                            //if next is 10
                            else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next is 100
                                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                                {
                                    out = out + numsExtracted[i + 1] * 100;
                                    i++;
                                    i++;
                                    //if next is 10
                                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                                    {
                                        out = out + numsExtracted[i + 1] * 10;
                                        i++;
                                        i++;
                                        // if next 2 is <10
                                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                        {
                                            out = out + +numsExtracted[i + 1];
                                            i++;
                                        }
                                    }
                                    else
                                    {
                                        // if next is <10
                                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                        {
                                            out = out + numsExtracted[i + 1];
                                            i++;
                                        }
                                    }
                                }

                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                }
                            }
                            // if next is <10
                            else
                            {
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                }
                            }
                        }
                    }
                }
                // if next is <10
                else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                {
                    out = out + numsExtracted[i + 1];
                    i++;
                }
                else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] == 1000)
                {
                    out = out + numsExtracted[i + 1];
                    i++;
                    // if next is 1000
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                    {
                        out = out * 1000;
                        i++;
                        // if next is 100
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                        {
                            out = out + numsExtracted[i + 1] * 100;
                            i++;
                            i++;
                            //if next is 10
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                }
                            }
                        }

                        //if next is 10
                        else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 100
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                            {
                                out = out + numsExtracted[i + 1] * 100;
                                i++;
                                i++;
                                //if next is 10
                                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                                {
                                    out = out + numsExtracted[i + 1] * 10;
                                    i++;
                                    i++;
                                    // if next 2 is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + +numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                                else
                                {
                                    // if next is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + numsExtracted[i + 1];
                                        i++;
                                    }
                                }
                            }

                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                            }
                        }
                        // if next is <10
                        else
                        {
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                            }
                        }
                    }
                }
            }

            //if next is 10
            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 10)
            {
                out = out * 10;
                i++;
                // if next is 0
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                {
                    out = out * 10;
                    i++;
                }
                // if next 1 is 1000
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                {
                    out = out * 1000;
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    // if next is 100
                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                    {
                        out = out + numsExtracted[i + 1] * 100;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        //if next is 10
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                    }

                    //if next is 10
                    else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                    {
                        out = out + numsExtracted[i + 1] * 10;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next 2 is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + +numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // if next is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                }

                // if next 2 is <10
                else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                {
                    out = out + numsExtracted[i + 1];
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                }
                else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] == 1000)
                {
                    out = out + numsExtracted[i + 1];
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    // if next 2 is 1000
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                    {
                        out = out * 1000;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next is 100
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                        {
                            out = out + numsExtracted[i + 1] * 100;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            //if next is 10
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                        }

                        //if next is 10
                        else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                    }
                }
            }

            // if next is <10
            while ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10)
            {
                out = out * 10 + numsExtracted[i + 1];
                i++;
                //if next is 10
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 10)
                {
                    out = out * 10;
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    // if next 1 is 1000
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                    {
                        out = out * 1000;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next is 100
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                        {
                            out = out + numsExtracted[i + 1] * 100;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            //if next is 10
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                        }

                        //if next is 10
                        else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                    }

                    // if next 2 is <10
                    else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] != 1000)
                    {
                        out = out + numsExtracted[i + 1];
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                    }
                    else if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 2] != 10 && numsExtracted[i + 2] == 1000)
                    {
                        out = out + numsExtracted[i + 1];
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next 2 is 1000
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                        {
                            out = out * 1000;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next is 100
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                            {
                                out = out + numsExtracted[i + 1] * 100;
                                i++;
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                                //if next is 10
                                if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                                {
                                    out = out + numsExtracted[i + 1] * 10;
                                    i++;
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                    // if next 2 is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + +numsExtracted[i + 1];
                                        i++;
                                        // if next is 0
                                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                        {
                                            out = out * 10;
                                            i++;
                                        }
                                    }
                                }
                                else
                                {
                                    // if next is <10
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                    {
                                        out = out + numsExtracted[i + 1];
                                        i++;
                                        // if next is 0
                                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                        {
                                            out = out * 10;
                                            i++;
                                        }
                                    }
                                }
                            }

                            //if next is 10
                            else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }

                // if next is 1000
                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 1000)
                {
                    out = out * 1000;
                    i++;
                    // if next is 0
                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                    {
                        out = out * 10;
                        i++;
                    }
                    // if next is 100
                    if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                    {
                        out = out + numsExtracted[i + 1] * 100;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        //if next is 10
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                        {
                            out = out + numsExtracted[i + 1] * 10;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            // if next 2 is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + +numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                        else
                        {
                            // if next is <10
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                            {
                                out = out + numsExtracted[i + 1];
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                            }
                        }
                    }

                    //if next is 10
                    else if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                    {
                        out = out + numsExtracted[i + 1] * 10;
                        i++;
                        i++;
                        // if next is 0
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                        {
                            out = out * 10;
                            i++;
                        }
                        // if next is 100
                        if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 100)
                        {
                            out = out + numsExtracted[i + 1] * 100;
                            i++;
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                            //if next is 10
                            if ((i + 2) < numsExtracted.size() && numsExtracted[i + 2] == 10)
                            {
                                out = out + numsExtracted[i + 1] * 10;
                                i++;
                                i++;
                                // if next is 0
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                {
                                    out = out * 10;
                                    i++;
                                }
                                // if next 2 is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + +numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                            else
                            {
                                // if next is <10
                                if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                                {
                                    out = out + numsExtracted[i + 1];
                                    i++;
                                    // if next is 0
                                    if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                                    {
                                        out = out * 10;
                                        i++;
                                    }
                                }
                            }
                        }

                        // if next 2 is <10
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + +numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                    // if next is <10
                    else
                    {
                        if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] < 10 && numsExtracted[i + 1] != 10 && numsExtracted[i + 1] != 1000)
                        {
                            out = out + numsExtracted[i + 1];
                            i++;
                            // if next is 0
                            if ((i + 1) < numsExtracted.size() && numsExtracted[i + 1] == 0)
                            {
                                out = out * 10;
                                i++;
                            }
                        }
                    }
                }
            }
        }

        // std::cout << "The Number: " << out << std::endl;
        listOfNumberExtracted.push_back(out);
        out = 0;
    }

    for (auto i = listOfNumberExtracted.begin(); i != listOfNumberExtracted.end();)
    {
        if (*i == 333)
            i = listOfNumberExtracted.erase(i);
        else
            i++;
    }

    //  for (auto it = listOfNumberExtracted.begin(); it != listOfNumberExtracted.end(); ++it)
    // {
    //     std::cout << ' ' << *it;
    // }
};

// NumberExtractor::NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
//                                  int startIndexExtractionAfter){

// };

std::vector<int> NumberExtractor::getListOfNumberExtracted() const
{
    return listOfNumberExtracted;
};

bool NumberExtractor::IfWordIsNumber(std::map<std::string, int> m, std::string word)
{
    std::map<std::string, int>::iterator it = m.find(word);
    if (it != m.end())
    {
        return true;
    }
    return false;
};

bool NumberExtractor::EndsWith(const std::string &mainStr, const std::string &toMatch)
{
    if (mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}