#include <vector>

#include <iostream>
#include <random>
#include <iomanip>


#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


#include <stdio.h>
#include <termios.h>        //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO


void pressKey()
{
    //the struct termios stores all kinds of flags which can manipulate the I/O Interface
    //I have an old one to save the old settings and a new 
    static struct termios oldt, newt;

    //tcgetattr gets the parameters of the current terminal
    //STDIN_FILENO will tell tcgetattr that it should write the settings
    // of stdin to oldt
    tcgetattr( STDIN_FILENO, &oldt);
    //now the settings will be copied 
    newt = oldt;

    //two of the c_lflag will be turned off
    //ECHO which is responsible for displaying the input of the user in the terminal
    //ICANON is the essential one! Normally this takes care that one line at a time will be processed
    //that means it will return if it sees a "\n" or an EOF or an EOL
    newt.c_lflag &= ~(ICANON | ECHO );      

    //Those new settings will be set to STDIN
    //TCSANOW tells tcsetattr to change attributes immediately. 
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //now the char wil be requested
    getchar();

    //the old settings will be written back to STDIN
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

}

enum class CurrentState
{
  NoState,
  LoopTill2,
  SkipOneLoop,
  SkipTwoLoops,
  LoopAgain
};
struct Gamer
{
  CurrentState currentState = CurrentState::NoState;
  int curPosition = 0;

  bool runOnce(std::mt19937& gen, std::uniform_int_distribution<>& dis)
  {
    auto offset = dis(gen);
    std::cout << "throwing result: " << offset << "| ";
     
    if (currentState == CurrentState::SkipOneLoop)
    {
      std::cout << "skipping loop, staying at the same position: " << curPosition << std::endl;
      currentState = CurrentState::NoState;
      return false;
    }
    else if (currentState == CurrentState::SkipTwoLoops)
    {
      std::cout << "skipping first loop from two, staying at the same position ..." << curPosition << std::endl;
      currentState = CurrentState::SkipOneLoop;
      return false;
    }

    if (currentState == CurrentState::LoopTill2)
    {
      if (offset != 2)
      {
        std::cout << "still will be waiting for 2" << std::endl;
      }
      else 
      {
        currentState = CurrentState::NoState;
      }
    }

    if (currentState == CurrentState::NoState)
    {
      if (curPosition + offset == 2)
      {
        currentState = CurrentState::LoopTill2;
        curPosition+=offset;
        std::cout << "trapped on 2. has to wait till two appears" << std::endl;
      }
      else if (curPosition + offset == 26)
      {
        currentState = CurrentState::SkipOneLoop;
        curPosition+=offset;
        std::cout << "trapped to 26. has two skip one loop" << std::endl;
      }
      else if (curPosition + offset == 33)
      {
        curPosition+=offset;
        std::cout << "got to 33. looping again" << std::endl;
        return true;
      }
      else if (curPosition + offset == 6)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 25;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 7)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 2;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 13)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 20;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 20)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 22;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 23)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 0;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 25)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 33;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 29)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 0;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 31)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 21;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 38)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 43;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 40)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 12;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 44)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition = 34;
        std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset >=46)
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        std::cout << "I won" << std::endl;
        return 0;
      }
      else
      {
        std::cout.width(5); std::cout << std::right << "from " << curPosition << " ";
        curPosition += offset;
        std::cout << "simple moving to: " << curPosition << std::endl;
      }
    }
    return false;
  }
};


int main()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 6);

    pressKey();

    Gamer gamer1;
    Gamer gamer2;
    int gamer = 1;
    while(true)
    {
      std::cout << "gamer: " << gamer << " ";
      if (gamer == 1)
      {
        if (gamer1.runOnce(gen, dis))
        {
          continue;
        }
        else
        {
          gamer = 2;
        }
      }
      else if (gamer == 2)
      {
        if (gamer2.runOnce(gen, dis))
        {
          continue;
        }
        else
        {
          gamer = 1;
        }
      }
      pressKey();
    }

  return 0;
}
