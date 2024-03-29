#queue

![simpsons queue](https://media4.giphy.com/media/l2JdWz78SwGlUV7OM/giphy.gif?cid=ecf05e476m4l07alexoya37pei10dqwthh3ay5ez3v69l7p2&rid=giphy.gif&ct=g)

Хүмүүс оочирлож зогсож байгааг нь төсөөлөх юм бол queue-г ойлгоход илүү хялбар болов уу.
жагсаалын эхэнд байгаа хүн нь түрүүлж үйлчлүүлээд, сүүлд ирсэн хүн нь цувааны хамгийн ард ирж зогсдогтой адил түрүүлж ирсэн нь түрүүлж үйлчлүүдэг зарчим.
queue нь дээрхи оочирлосон цуваатай адилхан эхэнд хийсэн элементийг нь авдаг, шинэ элемент нэмэхдээ ард нь нэмдэг бүтэц.

Доорхи тайлбарт а-г queue, х-г ямар нэгэн утга эсвэл хувьсагч гэе. 
Ихээр ашиглагддаг үйлдлүүдийг доор тайлбарлав.
| үйлдэл | тайлбар | хурд |
|---------|---------|-----|
| queue<int> a; | queue төрлийн хувьсаг зарлах. <br /> queue<int> гэж зарлавал, тухайн queue-д int төрлийн хувьсагчууд хийх боломжтой.<br /> queue<double> гэж зарлавал, тухайн queue-д double төрлийн хувьсагчууд хийх боломжтой.| O(1) |
| a.push(x) | a гэсэн queue-ийн ард нь х-г нэмнэ.<br /> жишээ нь а={3,1,4} үед a.push(8); гэсэн үйлдэл хийвэл a={3,1,4,8} болж хувирнэ.| O(1) |
| a.pop() | a-ийн хамгийн урд байгаа гишүүнийг авч хаях үйлдэл. <br /> жишээ нь a={3,1,4} үед a.pop() үйлдэл хийхэд a={1,4} болж хувирна. | O(1) |
| a.front() | хамгийн урд байгаа элемент-ийг унших үйлдэл.  | O(1) |
| a.size() | а дотор одоо хэдэн гишүүн байгааг буцаана. | O(1) |
| a.empty() | а дотор элемент байхгүй үед true, бусад үед false буцаана | O(1) |

Энэхүү бүтэцийг BFS(Breadth first search), хамгийн богино замыг олох алгоритм зэрэгт ихээр ашиглагддаг.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // жишээ: a-д янз янзын үйлдэл хийе
    queue<int> a;
    a.push(179); // энэ үед урд талаас нь жагсаавал {179} болно
    a.push(173); // энэ үед урд талаас нь жагсаавал  {179,173} болно
    a.push(156); // энэ үед урд талаас нь жагсаавал  {179, 173, 156} болно
    int x1 = a.front();
    a.pop(); // энэ үед урд талаас нь жагсаавал  {173, 156} болно
    a.push(117); // энэ үед урд талаас нь жагсаавал  {173, 156, 117} болно
    a.push(202); // энэ үед урд талаас нь жагсаавал  {173, 156, 117, 202} болно
    int x2 = a.front();
    a.pop(); // энэ үед урд талаас нь жагсаавал  {156, 117, 202} болно
    int x3 = a.front();
    int x4 = a.size();
    int x5 = 0; if (a.empty()) x5 = 10000;
    cout << x1 << " " << x2 << " "<< x3 << " " << x4 << " " << x5 << endl;
    //x1 = 179, x2 = 173, x3 = 156, x4 = 3, x5 = 0 болно
    return 0;
}
```