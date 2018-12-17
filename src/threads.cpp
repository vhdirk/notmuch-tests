#define BOOST_TEST_MODULE "threads"
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <notmuch.h>

BOOST_AUTO_TEST_CASE(iter)
{

    std::string dbpath = "/home/dvhaeren/.mail";
    notmuch_database_t* database;
    notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

    notmuch_thread_t *thread;

    {
        notmuch_query_t* query = notmuch_query_create(database, "*");
        notmuch_threads_t* threads;

        status = notmuch_query_search_threads(query, &threads);

        thread = notmuch_threads_get(threads);

        auto id = notmuch_thread_get_thread_id(thread);
        auto subject = notmuch_thread_get_subject(thread);
        std::cout << "ID: " << id << ", Subject: " << subject << std::endl;

        notmuch_thread_destroy(thread);

        thread = notmuch_threads_get(threads);
        //notmuch_thread_destroy(thread);

        {
            auto id = notmuch_thread_get_thread_id(thread);
            auto subject = notmuch_thread_get_subject(thread);
            std::cout << "ID: " << id << ", Subject: " << subject << std::endl;
        }

        notmuch_threads_destroy(threads);
        notmuch_query_destroy(query);

    }
    notmuch_database_destroy(database);

    auto id = notmuch_thread_get_thread_id(thread);
    auto subject = notmuch_thread_get_subject(thread);
    std::cout << "ID: " << id << ", Subject: " << subject << std::endl;
}
