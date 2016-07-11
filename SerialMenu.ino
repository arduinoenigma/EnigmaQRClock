byte numberstocollect = 0;
byte storenumbersin = 0;
byte collectednumber = 0;
byte finishedcollection = 1;


//to setup r1h15m22s10u10dx
//bug: h1m1s1 does not work

void SerialFSM()
{

  char KeyPressed = 0;

  if (Serial.available())
  {
    KeyPressed = Serial.read();

    switch (KeyPressed)
    {
        //set hours
      case 'H':
      case 'h':
        {
          collectednumber = 0;
          numberstocollect = 2;
          storenumbersin = 1;
          break;
        }

        //set minutes
      case 'M':
      case 'm':
        {
          collectednumber = 0;
          numberstocollect = 2;
          storenumbersin = 2;
          break;
        }

        //set seconds
      case 'S':
      case 's':
        {
          collectednumber = 0;
          numberstocollect = 2;
          storenumbersin = 3;
          break;
        }

        //display AM/PM or 24hr
      case 'P':
      case 'p':
        {
          collectednumber = 0;
          numberstocollect = 1;
          storenumbersin = 4;
          break;
        }

        //update every x seconds
      case 'U':
      case 'u':
        {
          collectednumber = 0;
          numberstocollect = 2;
          storenumbersin = 5;
          break;
        }

        // set rotation
      case 'R':
      case 'r':
        {
          collectednumber = 0;
          numberstocollect = 1;
          storenumbersin = 6;
          break;
        }

        // draw the time
      case 'D':
      case 'd':
        {
          Serial.print(hours);
          Serial.print(":");
          Serial.print(mins);
          Serial.print(":");
          Serial.println(secs);
          break;
        }

        // start clock
      case 'X':
      case 'x':
        {
          ul_LastGenerated = millis();
          advancetime();
          advancetime();
          generate();
          break;
        }

        // collect numeric parameter or ; as separator
      default:
        {
          if (numberstocollect)
          {
            finishedcollection = 0;
            if ((KeyPressed >= '0') && (KeyPressed <= '9'))
            {
              collectednumber = collectednumber * 10 + (KeyPressed - '0');
              numberstocollect--;
              if (numberstocollect == 0)
              {
                finishedcollection = 1;
              }
            }
            if (KeyPressed == ';')
            {
              finishedcollection = 1;
            }
          }

          if (finishedcollection)
          {
            finishedcollection = 0;

            switch (storenumbersin)
            {
              case 1:
                {
                  hours = collectednumber;
                  break;
                }
              case 2:
                {
                  mins = collectednumber;
                  break;
                }
              case 3:
                {
                  secs = collectednumber;
                  break;
                }
              case 4:
                {
                  ampm = collectednumber;
                  break;
                }
              case 5:
                {
                  if ((collectednumber == 1) || (collectednumber == 5) || (collectednumber == 10) || (collectednumber == 15) || (collectednumber == 20) || (collectednumber == 30) || (collectednumber == 60))
                  {
                    update = collectednumber;
                  }
                  break;
                }
              case 6:
                {
                  if (collectednumber < 4)
                  {
                    rotation = collectednumber;
                    
                    if ((rotation==0) || (rotation==2))
                    {
                      xo = 15;
                      yo = 55;
                    }
                    else
                    {
                      yo = 15;
                      xo = 55;
                    }
                    
                    Tft.setRotation(rotation);
                    Tft.fillScreen(BLACK);
                    printcode(&outputmatrix[0]);
                  }
                  break;
                }
            }

          }

          break;
        }
    }


  }
}
