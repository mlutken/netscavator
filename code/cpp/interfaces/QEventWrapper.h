#ifndef CRAWL_QEVENTWRAPPER_H
#define CRAWL_QEVENTWRAPPER_H

#include <typeinfo>
#include <QEvent>
#include <QHash>


namespace crawl {

/**
\see http://stackoverflow.com/questions/2248009/qt-defining-a-custom-event-type
*/
template <typename T> class QEventWrapper : public QEvent {
public:
   QEventWrapper()
       : QEvent(staticType())
   {}

   static QEvent::Type staticType() {
      static int type = QEvent::registerEventType();
      return static_cast<QEvent::Type>(type);
   }

   static int localDurableType() {
      static int type = qHash(typeid(T).name());
      return type;
   }
};



} // namespace crawl

#define DEFINE_QEVENT(Name) \
   class Name : public crawl::QEventWrapper< Name > \
   { static int durableType() { \
       static int durable = static_cast<int>(qHash(#Name)); return durable; \
     } };


#define DEFINE_QEVENT1(EventName, DataType1, DataName1) \
class EventName : public crawl::QEventWrapper< EventName > \
{ \
public: \
    explicit EventName(const DataType1& _##DataName1) \
    : DataName1 (_##DataName1) {} \
    DataType1 DataName1; \
private: \
    static int durableType() \
    { \
        static int durable = static_cast<int>(qHash(#EventName)); \
        return durable; \
    } \
};


#define DEFINE_QEVENT2(EventName, DataType1, DataName1, DataType2, DataName2) \
class EventName : public crawl::QEventWrapper< EventName > \
{ \
public: \
    explicit EventName(const DataType1& _##DataName1, const DataType2& _##DataName2) \
    : DataName1 (_##DataName1), \
      DataName2 (_##DataName2) {} \
    DataType1 DataName1; \
    DataType2 DataName2; \
private: \
    static int durableType() \
    { \
        static int durable = static_cast<int>(qHash(#EventName)); \
        return durable; \
    } \
};

#endif // CRAWL_QEVENTWRAPPER_H
