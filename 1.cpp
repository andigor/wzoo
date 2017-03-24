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


#include <future>
#include <atomic>

#include <sstream>

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

enum class Status
{
  Continue,
  LoopAgain,
  Won
};

struct Gamer
{
  CurrentState currentState = CurrentState::NoState;
  int curPosition = 0;
  void printMovement(int from, int offset)
  {
    //std::cout << from << "->" << from + offset << " ";
  }
  Status runOnce(std::mt19937& gen, std::uniform_int_distribution<>& dis)
  {
    auto offset = dis(gen);
    //std::cout << "throwing result: " << offset << "| ";
     
    if (currentState == CurrentState::SkipOneLoop)
    {
      //std::cout << "skipping loop, staying at the same position: " << curPosition << std::endl;
      currentState = CurrentState::NoState;
      return Status::Continue;
    }
    else if (currentState == CurrentState::SkipTwoLoops)
    {
      //std::cout << "skipping first loop from two, staying at the same position ..." << curPosition << std::endl;
      currentState = CurrentState::SkipOneLoop;
      return Status::Continue;
    }

    if (currentState == CurrentState::LoopTill2)
    {
      if (offset != 2)
      {
        //std::cout << "still will be waiting for 2" << std::endl;
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
        printMovement(curPosition, offset);
        curPosition+=offset;
        //std::cout << "trapped on 2. has to wait till two appears" << std::endl;
      }
      else if (curPosition + offset == 26)
      {
        currentState = CurrentState::SkipOneLoop;
        printMovement(curPosition, offset);
        curPosition+=offset;
        //std::cout << " have two skip one loop" << std::endl;
      }
      else if (curPosition + offset == 33)
      {
        curPosition+=offset;
        printMovement(curPosition, offset);
        //std::cout << " looping again" << std::endl;
        return Status::LoopAgain;
      }
      else if (curPosition + offset == 6)
      {
        printMovement(curPosition, offset);
        curPosition = 25;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 7)
      {
        printMovement(curPosition, offset);
        curPosition = 2;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 13)
      {
        printMovement(curPosition, offset);
        curPosition = 20;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 20)
      {
        printMovement(curPosition, offset);
        curPosition = 22;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 23)
      {
        printMovement(curPosition, offset);
        curPosition = 0;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 25)
      {
        printMovement(curPosition, offset);
        curPosition = 33;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 29)
      {
        printMovement(curPosition, offset);
        curPosition = 0;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 31)
      {
        printMovement(curPosition, offset);
        curPosition = 21;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 38)
      {
        printMovement(curPosition, offset);
        curPosition = 43;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 40)
      {
        printMovement(curPosition, offset);
        curPosition = 12;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset == 44)
      {
        printMovement(curPosition, offset);
        curPosition = 34;
        //std::cout << "moving to " << curPosition << std::endl;
      }
      else if (curPosition + offset >=46)
      {
        printMovement(curPosition, offset);
        //std::cout << "I won" << std::endl;
        return Status::Won;
      }
      else
      {
        printMovement(curPosition, offset);
        curPosition += offset;
        //std::cout << std::endl;
        ////std::cout << "simple moving to: " << curPosition << std::endl;
      }
    }
    return Status::Continue;
  }
};


int play(size_t& player1, size_t& player2)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 6);

    //pressKey();

    Gamer gamer1;
    Gamer gamer2;
    int gamer = 1;
    while(true)
    {
      //std::cout << "gamer " << gamer << ": ";
      if (gamer == 1)
      {
        auto s = gamer1.runOnce(gen, dis);
        if (s == Status::LoopAgain)
        {
          continue;
        }
        else if (s == Status::Continue)
        {
          gamer = 2;
        }
        else if (s == Status::Won)
        {
          ++player1;
          return 0;
        }
      }
      else if (gamer == 2)
      {
        auto s = gamer2.runOnce(gen, dis);
        if (s == Status::LoopAgain)
        {
          continue;
        }
        else if (s == Status::Continue)
        {
          gamer = 1;
        }
        else if (s == Status::Won)
        {
          ++player2;
          return 0;
        }
      }
      //:w
      //pressKey();
    }
}

void func(size_t count, std::atomic<size_t>& player1, std::atomic<size_t>& player2)
{
  size_t p1{}, p2{};
  size_t i = 0;
  for (; i<count; ++i)
  {
    //std::cerr << i << std::endl;
    play(p1, p2);
  }

  player1.fetch_add(p1);
  player2.fetch_add(p2);

  std::string s;
  std::stringstream ss(s);
  ss << "full iterations: " << p1 + p2 << " and i: " <<  i << " player2: " << player1 << " player2: " << player2 << std::endl;
  std::cout << ss.str(); 
}

int main()
{
  std::atomic<size_t> player1{}, player2{};

  player1.store(0);
  player2.store(0);

  size_t count = 100000000;
  auto f = [&](){
             func(count / 8, player1, player2); 
           };
  auto f1 = std::async(std::launch::async, f);
  auto f2 = std::async(std::launch::async, f);
  auto f3 = std::async(std::launch::async, f);
  auto f4 = std::async(std::launch::async, f);
  auto f5 = std::async(std::launch::async, f);
  auto f6 = std::async(std::launch::async, f);
  auto f7 = std::async(std::launch::async, f);
  auto f8 = std::async(std::launch::async, f);

  f1.wait();
  f2.wait();
  f3.wait();
  f4.wait();
  f5.wait();
  f6.wait();
  f7.wait();
  f8.wait();

  if (player1 + player2 != count)
  {
    std::cout << "error " << std::endl;
  }

  std::cout << "player1: " << player1 << std::endl;
  std::cout << "player2: " << player2 << std::endl;

  return 0;
}
