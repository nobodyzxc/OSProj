#ifndef _REQUEST_H_
#define _REQUEST_H_
#include <pthread.h>

#define MIN_QUOTA 20
#define INT_QUOTA 50
#define MAX_QUOTA (MIN_QUOTA + INT_QUOTA - 1)

class Bank;
class RequestGenerator;

class Request{
    public:
        bool nextAdvance;
        /* flag to see
         * if the client can start next request */
        int quota , krona , idx;
        /* quota : max krona that client can borrow
         * krona : current krona
         * idx   : client's id */
        void (*display)(int , int , int);
        /* function to show client's status */
        Request(Bank &bnk ,
                RequestGenerator &gen ,
                int quo , int id);

        void active();
        /* start client's thread */
        void addKrona(int amount);
        /* add client's krona (request succeeded) */
    private:
        Bank &bank;
        pthread_t threadID;
        RequestGenerator &generator;

        static void *running(void *ptr);
        /* thread runs the function */
        void advanceKrona(int amount);
        /* send a request to bank */
        void repay();
        /* get all krona , then repay to bank */
};

class RequestGenerator{
    public:
        int curIdx;
        /* count the ids have distributed */
        bool power;
        /* switch for power on or power off */
        RequestGenerator(
                Bank &bnk ,
                void (*_display)(int , int , int));

        void active(int maximum);
        /* start the thread */
        void genReq(int quo);
        /* generate the clients */
        void (*display)(int , int , int);

    private:
        Bank &bank;
        pthread_t threadID;
        int maxCust;
        /* max number of clients it can generate */
        static void *running(void *ptr);
};
#endif
