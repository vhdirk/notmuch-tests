#define BOOST_TEST_MODULE "messages"
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <notmuch.h>

// BOOST_AUTO_TEST_CASE(query)
// {

//     std::string dbpath = "/home/dvhaeren/.mail";
//     notmuch_database_t* database;
//     notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

//     notmuch_message_t *message;
//     notmuch_query_t* query = notmuch_query_create(database, "*");
//     notmuch_messages_t *messages;

//     status = notmuch_query_search_messages(query, &messages);

//     for (;notmuch_messages_valid(messages);
//          notmuch_messages_move_to_next(messages))
//     {
//         message = notmuch_messages_get(messages);
//         const char *mid = notmuch_message_get_message_id(message);
//         fprintf(stdout, "Message: %s\n", mid);
//         notmuch_message_destroy(message);
//     }

//     {
//         const char *mid = notmuch_message_get_message_id(message);
//         fprintf(stdout, "Message: %s\n", mid);
//         notmuch_message_destroy(message);
//     }

//     notmuch_query_destroy(query);
//     notmuch_database_destroy(database);
// }

BOOST_AUTO_TEST_CASE(threads)
{

    std::string dbpath = "/home/dvhaeren/.mail";
    notmuch_database_t *database;
    notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

    notmuch_query_t *query = notmuch_query_create(database, "*");
    notmuch_messages_t *messages;
    notmuch_threads_t *threads;
    notmuch_thread_t *thread;
    notmuch_message_t *message;

    status = notmuch_query_search_threads(query, &threads);
    thread = notmuch_threads_get(threads);
    messages = notmuch_thread_get_messages(thread);
    notmuch_thread_destroy(thread);

    for (;
         notmuch_messages_valid(messages);
         notmuch_messages_move_to_next(messages))
    {
        notmuch_message_t *message = notmuch_messages_get(messages);
        const char *mid = notmuch_message_get_message_id(message);
        fprintf(stdout, "Message: %s\n", mid);
        //notmuch_message_destroy(message);
    }

    // for (messages = notmuch_thread_get_messages(thread);
    //      notmuch_messages_valid(messages);
    //      notmuch_messages_move_to_next(messages))
    // {
    //     notmuch_message_t *message = notmuch_messages_get(messages);
    //     const char *mid = notmuch_message_get_message_id(message);
    //     fprintf(stdout, "Message: %s\n", mid);
    //     notmuch_message_destroy(message);
    // }


    notmuch_messages_destroy(messages);

    notmuch_query_destroy(query);

    notmuch_database_destroy(database);
}

BOOST_AUTO_TEST_CASE(replies)
{

    std::string dbpath = "/home/dvhaeren/.mail";
    notmuch_database_t *database;
    notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

    notmuch_query_t *query = notmuch_query_create(database, "*");
    notmuch_messages_t *messages;
    notmuch_messages_t *replies;

    notmuch_threads_t *threads;
    notmuch_thread_t *thread;
    notmuch_message_t *message;

    status = notmuch_query_search_threads(query, &threads);

    int cnt = 0;

    for (;notmuch_threads_valid(threads);
         notmuch_threads_move_to_next(threads))
    {
        thread = notmuch_threads_get(threads);

        int i = 0;
        for (messages = notmuch_thread_get_messages(thread);
             notmuch_messages_valid(messages);
             notmuch_messages_move_to_next(messages))
        {
            message = notmuch_messages_get(messages);

            int j = 0;
            replies = notmuch_message_get_replies(message);
            for (; notmuch_messages_valid(replies);
                 notmuch_messages_move_to_next(replies))
            {

                notmuch_message_t *reply = notmuch_messages_get(replies);
                const char *mid = notmuch_message_get_message_id(reply);
                fprintf(stdout, "Message: %s\n", mid);
                notmuch_message_destroy(reply);
                break;
                j++;
            }
            notmuch_messages_destroy(replies);
            replies = notmuch_message_get_replies(message);

            for (; notmuch_messages_valid(replies);
                 notmuch_messages_move_to_next(replies))
            {

                notmuch_message_t *reply = notmuch_messages_get(replies);
                const char *mid = notmuch_message_get_message_id(reply);
                fprintf(stdout, "Message: %s\n", mid);
                // notmuch_message_destroy(reply);
            }

            // if (i > 0 && j > 0)
            //     fprintf(stdout, "%d, Message: %d, %d\n", cnt, i, j);
            //notmuch_message_destroy(message);
            i++;
        }

        cnt++;
    }

    // for (messages = notmuch_thread_get_messages(thread);
    //      notmuch_messages_valid(messages);
    //      notmuch_messages_move_to_next(messages))
    // {
    //     notmuch_message_t *message = notmuch_messages_get(messages);
    //     const char *mid = notmuch_message_get_message_id(message);
    //     fprintf(stdout, "Message: %s\n", mid);
    //     notmuch_message_destroy(message);
    // }

    // notmuch_messages_destroy(messages);

    notmuch_query_destroy(query);

    notmuch_database_destroy(database);
}
