//#ifndef SORTABLE_LIST_H_INCLUDED
//#define SORTABLE_LIST_H_INCLUDED
//#include "List.h"
//#include "Queue.h"
//#include <string>
//
////class Key{
////public:
////    Key(char x)
////    {
////        key = x;
////    }
////    char the_key() const
////    {
////        return key;
////    }
////private:
////    char key;
////};
////
////bool operator ==(const Key&x, const Key &y)
////{
////    return x.the_key() == y.the_key();
////}
//
//const int max_chars = 28;
//int alphabetic_order(char c);
//
//class Record
//{
//public:
//    char key_letter(int position) const
//    {
//        if(position<0 || position>key_size_)
//            return ' ';
//        else
//            return key[position];
//    }
//    Record(string key_);
////    operator Key() const;   //cast to key
//private:
//    string key;
//    int key_size_;
//};
//
//Record::Record(string key_)
//{
//    key = key_;
//    key_size_ = key_.length();
//}
//
//
//template<class Record>
//class Sortable_list:public List<Record>
//{
//public:
//    void radix_sort();
//    int Get_max_key_size();
//private:
//    void rethread(CirQueue<Record> queues[]);  //recombine the queues.
//};
//
//
//template <class Record>
//void Sortable_list<Record>::radix_sort()
//{
//    int key_size = Get_max_key_size();
//    Record data;
//    CirQueue<Record> queues[max_chars];
//    for(int position = key_size-1; position>=0; position--)
//    {
//        while(remove(0,data) == success)
//        {
//            int queue_number = alphabetic_order(data.key_letter(position));
//            queues[queue_number].append(data);
//        }
//        rethread(queues);
//    }
//}
//
//
//template<class Record>
//int Sortable_list<Record>::Get_max_key_size()
//{
//    int key_size = 0;
//    for(int i=0; i<this.size(); i++)
//    {
//        if(this.entry[i].key_size_ > key_size)
//            key_size = this.entry[i].key_size_;
//    }
//    return key_size;
//}
//
//template<class Record>
//void Sortable_list<Record>::rethread(CirQueue<Record> queues[])
//{
//    Record data;
//    for(int i=0; i<max_chars; i++)
//    {
//        while(!queues[i].empty())
//        {
//            queues[i].retrieve(data);
//            insert(this.size(), data);
//            queues[i].serve();
//        }
//    }
//}
//
//int alphabetic_order(char c)
//{
//    if (c==' ')return 0;
//    else if('a'<=c && c<='z') return c-'a'+1;
//    else if('A'<=c && c<='Z') return c-'A'+1;
//    return 27;
//}
//
//#endif // SORTABLE_LIST_H_INCLUDED
