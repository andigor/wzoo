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
#include <vector>

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

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


struct NewState
{
  CurrentState currentState;
  Status       status;
  size_t       pos;
};


void fillNoState_States(std::vector<NewState>& states )
{
  size_t new_pos = 0;
  new_pos= 1; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos= 2; states.push_back(NewState{CurrentState::LoopTill2,   Status::Continue, new_pos});
  new_pos= 3; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos= 4; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos= 5; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos= 6; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      25});
  new_pos= 7; states.push_back(NewState{CurrentState::NoState,     Status::Continue,       2});
  new_pos= 8; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos= 9; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=10; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=11; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=12; states.push_back(NewState{CurrentState::SkipTwoLoops,Status::Continue, new_pos});
  new_pos=13; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      20});
  new_pos=14; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=15; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=16; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=17; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=18; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=19; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=10; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      22});
  new_pos=21; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=22; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=23; states.push_back(NewState{CurrentState::NoState,     Status::Continue,       0});
  new_pos=24; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=25; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      33});
  new_pos=26; states.push_back(NewState{CurrentState::SkipOneLoop, Status::Continue, new_pos});
  new_pos=27; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=28; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=29; states.push_back(NewState{CurrentState::NoState,     Status::Continue,       0});
  new_pos=30; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=31; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      21});
  new_pos=32; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=33; states.push_back(NewState{CurrentState::NoState,     Status::LoopAgain,new_pos});
  new_pos=34; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=35; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=36; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=37; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=38; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      43});
  new_pos=39; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=40; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      12});
  new_pos=41; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=42; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=43; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=44; states.push_back(NewState{CurrentState::NoState,     Status::Continue,      34});
  new_pos=45; states.push_back(NewState{CurrentState::NoState,     Status::Continue, new_pos});
  new_pos=46; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
  new_pos=47; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
  new_pos=48; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
  new_pos=49; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
  new_pos=50; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
  new_pos=51; states.push_back(NewState{CurrentState::NoState,     Status::Won,           46});
}

struct Gamer
{
  CurrentState currentState = CurrentState::NoState;
  int curPosition = 0;
  void printMovement(int from, int offset)
  {
    //std::cout << from << "->" << from + offset << " ";
  }
  Status runOnce(std::mt19937& gen, std::uniform_int_distribution<>& dis, const std::vector<NewState>& states)
  {
    auto offset = dis(gen);
    //std::cout << "throwing result: " << offset << "| ";

    if (currentState == CurrentState::NoState)
    {
      auto new_pos = curPosition + offset;
      const auto& s = states[new_pos];
      currentState = s.currentState;
      curPosition = s.pos;
      return s.status;
    }
     
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

  }
};


inline int play(size_t& player1, size_t& player2, std::mt19937& gen, std::uniform_int_distribution<>& dis, const std::vector<NewState>& states)
{

    //pressKey();

    Gamer gamer1;
    Gamer gamer2;

    while(true)
    {
      //std::cout << "gamer " << gamer << ": ";
      {
        auto s = gamer1.runOnce(gen, dis, states);
        if (s == Status::LoopAgain)
        {
          s = gamer1.runOnce(gen, dis, states);
        }
        
        if (s == Status::Won)
        {
          ++player1;
          return 0;
        }
      }
      {
        auto s = gamer2.runOnce(gen, dis, states);
        if (s == Status::LoopAgain)
        {
          s = gamer2.runOnce(gen, dis, states);
        }
        
        if (s == Status::Won)
        {
          ++player2;
          return 0;
        }
      }
    }
}

inline void func(size_t count, std::atomic<size_t>& player1, std::atomic<size_t>& player2, const std::vector<NewState>& states)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(1, 6);
  size_t p1{}, p2{};
  size_t i = 0;
  for (; i<count; ++i)
  {
    //std::cerr << i << std::endl;
    play(p1, p2, gen, dis, states);
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
  std::vector<NewState> NoState_States;
  fillNoState_States(NoState_States);

  size_t count = 10000000;
  auto f = [&](){
             func(count , player1, player2, NoState_States); 
           };
  auto f1 = std::async(std::launch::async, f);
  //auto f2 = std::async(std::launch::async, f);
  //auto f3 = std::async(std::launch::async, f);
  //auto f4 = std::async(std::launch::async, f);
  //auto f5 = std::async(std::launch::async, f);
  //auto f6 = std::async(std::launch::async, f);
  //auto f7 = std::async(std::launch::async, f);
  //auto f8 = std::async(std::launch::async, f);

  f1.wait();
  //f2.wait();
  //f3.wait();
  //f4.wait();
  //f5.wait();
  //f6.wait();
  //f7.wait();
  //f8.wait();

  if (player1 + player2 != count)
  {
    std::cout << "error " << std::endl;
  }

  std::cout << "player1: " << player1 << std::endl;
  std::cout << "player2: " << player2 << std::endl;

  return 0;
}
