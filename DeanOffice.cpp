#include <string>
#include <iostream>
#include "DeanOffice.hpp"

	DeanOffice::DeanOffice(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_DeanOffice)
    {
        int a;
        cin>>a;

        docbuf = new int*[DOC_TYPES];
        for(int i=0;i<DOC_TYPES;i++)
            docbuf[i] = new int[DOC_BUF_SIZE];
        head = new int[DOC_TYPES];
        tail = new int[DOC_TYPES];
        cnt = new int[DOC_TYPES];
        docbuf_empty = new condition_variable[DOC_TYPES];
        docbuf_full = new condition_variable[DOC_TYPES];
        docbuf_mutex = new mutex[DOC_TYPES];

        stamps = new bool[STAMPS_CNT];
        for(int i=0;i<STAMPS_CNT; i++)
        {
            stamps[i] = true;
        }
        stamps_cond = new condition_variable[STAMPS_CNT];
        stamps_mutex = new mutex;
    }

    DeanOffice::DeanOffice()
        : Room("dziekanat", 10, RoomType::E_DeanOffice)
    {
        docbuf = new int*[DOC_TYPES];
        for(int i=0;i<DOC_TYPES;i++)
            docbuf[i] = new int[DOC_BUF_SIZE];
        head = new int[DOC_TYPES];
        tail = new int[DOC_TYPES];
        cnt = new int[DOC_TYPES];
        docbuf_empty = new condition_variable[DOC_TYPES];
        docbuf_full = new condition_variable[DOC_TYPES];
        docbuf_mutex = new mutex[DOC_TYPES];

        stamps = new bool[STAMPS_CNT];
        stamps_cond = new condition_variable[STAMPS_CNT];
        stamps_mutex = new mutex;
    }

    DeanOffice::~DeanOffice()
    {
        delete docbuf,head,tail,cnt,docbuf_empty,docbuf_full,docbuf_mutex;
        delete stamps,stamps_cond,stamps_mutex;
    }

    void DeanOffice::virtual_function(){}


    void DeanOffice::printDocBuf()
{
    cout<<"typ  | stosy\n"<<"----------------------------";
    for(int i=0;i<DOC_TYPES;i++)
    {
        cout<<endl<<i<<".   |";
        //for(int j=0;j<doc_types_cnt[i];j++)
        for(int j=0;j<DOC_TYPES;j++)
        {
            cout<<docbuf[i][j]<<"  ";
        }
    }
    cout<<endl;
}