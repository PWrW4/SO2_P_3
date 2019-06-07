#include <string>
#include "DeanOffice.hpp"

	DeanOffice::DeanOffice(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_DeanOffice)
    {
        docbuf = new int[DOC_BUF_SIZE];
        head = new int[DOC_TYPES];
        tail = new int[DOC_TYPES];
        cnt = new int[DOC_TYPES];
        docbuf_empty = new condition_variable[DOC_TYPES];
        docbuf_full = new condition_variable[DOC_TYPES];
        docbuf_mutex = new mutex[DOC_TYPES];

        stamps = new bool[STAMPS_CNT];
        stamps_cond = new condition_variable[STAMPS_CNT];
        stamps_mutex = new mutex[STAMPS_CNT];
    }

    DeanOffice::DeanOffice()
    {
        docbuf = new int[DOC_BUF_SIZE];
        head = new int[DOC_TYPES];
        tail = new int[DOC_TYPES];
        cnt = new int[DOC_TYPES];
        docbuf_empty = new condition_variable[DOC_TYPES];
        docbuf_full = new condition_variable[DOC_TYPES];
        docbuf_mutex = new mutex[DOC_TYPES];

        stamps = new bool[STAMPS_CNT];
        stamps_cond = new condition_variable[STAMPS_CNT];
        stamps_mutex = new mutex[STAMPS_CNT];
    }

    DeanOffice::~DeanOffice()
    {
        delete docbuf,head,tail,cnt,docbuf_empty,docbuf_full,docbuf_mutex;
        delete stamps,stamps_cond,stamps_mutex;
    }