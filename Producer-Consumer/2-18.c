// 生产者消费者 伪代码

#define N 100           //缓冲区中槽的数目
typedef int semaphore;  //信号量是一种特殊的整数型数据
semaphore mutex = 1;    //控制对临界区的访问
semaphore full = 0;     //计数缓冲区的满槽数目
semaphore empty = N;    //计数缓冲区的空槽数目


//生产者
void producer(void) 
{
    int item;

    while (TRUE) 
    {
        item = produce_item();      //产生放在缓冲区的一些数据
        down(&empty);               //空槽数目减一
        down(&mutex);               //进入临界区
        insert_item(item);          //将新数据放到缓冲区
        up(&mutex);                 //出临界区
        up(&full);                  //满槽加一
    }
}

//消费者
void consumer(void) 
{
    int item;

    while (TRUE) 
    {
        down(&full);                //满槽减一
        down(&mutex);               //进入临界区
        item = remove_item();       //拿走数据
        up(&mutex);                 //离开临界区
        up(&empty);                 //空槽加一
        consumer_item(item);        //处理数据项
    }
}