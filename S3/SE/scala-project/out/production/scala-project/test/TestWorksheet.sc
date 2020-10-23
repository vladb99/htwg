val x,y = 1
x+y
x-y

17*4

def f(x:Int) = x+1

f(20)

f(99)

def f2(x:Boolean) = !x

val konstante = f2(true)

println(konstante)

object Cell{
    var size = 9
    def setSize(s:Int): Unit ={
        size = s
    }
}

Cell.size

Cell.setSize(40)

Cell.size