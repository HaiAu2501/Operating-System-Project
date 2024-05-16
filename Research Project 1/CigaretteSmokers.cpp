#include <iostream>
#include <semaphore>
#include <mutex>
#include <thread>
#include <cassert>

using namespace std;

class CigaretteSmokers {
    public:

    static counting_semaphore<INT_MAX> tobaccoSem;
    static counting_semaphore<INT_MAX> paperSem;
    static counting_semaphore<INT_MAX> matchSem;

    static counting_semaphore<INT_MAX> tobacco;
    static counting_semaphore<INT_MAX> paper;
    static counting_semaphore<INT_MAX> match;

    static int numTobacco;
    static int numPaper;
    static int numMatch;

    static mutex coutMutex;
    static mutex pusherMutex;

    static void smokerWithTobacco() {
        while (true) {
            tobaccoSem.acquire();
            coutMutex.lock();
            cout << "Smoker with tobacco is making cigarette.\n";
            cout << "Smoker with tobacco is smoking.\n";
            coutMutex.unlock();
        }
    }

    static void smokerWithPaper() {
        while (true) {
            paper.acquire();
            coutMutex.lock();
            cout << "Smoker with paper is making cigarette.\n";
            cout << "Smoker with paper is smoking.\n";
            coutMutex.unlock();
        }
    }

    static void smokerWithMatch() {
        while (true) {
            matchSem.acquire();
            coutMutex.lock();
            cout << "Smoker with match is making cigarette.\n";
            cout << "Smoker with match is smoking.\n";
            coutMutex.unlock();
        }
    }

    static void agent() {
        while (true) {
            int random_number = rand() % 3;
            switch (random_number) {
                case 0:
                    tobacco.release();
                    paper.release();
                    break;
                
                case 1:
                    paper.release();
                    match.release();
                    break;

                case 2:
                    match.release();
                    tobacco.release();
                    break;

                default:
                    assert(false);
                    break;
            }
            coutMutex.lock();
            cout << numTobacco << ' ' << numPaper << ' ' << numMatch << '\n';
            coutMutex.unlock();
        }
    }

    static void pusherA() {
        while (true) {
            tobacco.acquire();
            pusherMutex.lock(); 
            if (numPaper) {
                --numPaper;
                matchSem.release();
            }
            else if (numMatch) {
                --numMatch;
                paperSem.release();
            }
            else {
                ++numTobacco;
            }
            pusherMutex.unlock();
        }
    }

    static void pusherB() {
        while (true) {
            paper.acquire();
            pusherMutex.lock(); 
            if (numMatch) {
                --numMatch;
                tobaccoSem.release();
            }
            else if (numTobacco) {
                --numTobacco;
                match.release();
            }
            else {
                ++numPaper;
            }
            pusherMutex.unlock();
        }
    }

    static void pusherC() {
        while (true) {
            match.acquire();
            pusherMutex.lock(); 
            if (numTobacco) {
                --numTobacco;
                paperSem.release();
            }
            else if (numPaper) {
                --numPaper;
                tobaccoSem.release();
            }
            else {
                ++numMatch;
            }
            pusherMutex.unlock();
        }
    }

    static void simulate() {
        thread agentThread(agent);

        thread pusherAThread(pusherA);
        thread pusherBThread(pusherB);
        thread pusherCThread(pusherC);

        thread smokerWithTobaccoThread(smokerWithTobacco);
        thread smokerWithPaperThread(smokerWithPaper);
        thread smokerWithMatchThread(smokerWithMatch);

        agentThread.join();

        pusherAThread.join();
        pusherBThread.join();
        pusherCThread.join();

        smokerWithTobaccoThread.join();
        smokerWithPaperThread.join();
        smokerWithMatchThread.join();
    }
};

counting_semaphore<INT_MAX> CigaretteSmokers::tobaccoSem{0};
counting_semaphore<INT_MAX> CigaretteSmokers::paperSem{0};
counting_semaphore<INT_MAX> CigaretteSmokers::matchSem{0};

counting_semaphore<INT_MAX> CigaretteSmokers::tobacco{0};
counting_semaphore<INT_MAX> CigaretteSmokers::paper{0};
counting_semaphore<INT_MAX> CigaretteSmokers::match{0};

mutex CigaretteSmokers::coutMutex;
mutex CigaretteSmokers::pusherMutex;

int CigaretteSmokers::numTobacco = 0;
int CigaretteSmokers::numPaper = 0;
int CigaretteSmokers::numMatch = 0;

int main() {
    CigaretteSmokers::simulate();
    return 0;
}
