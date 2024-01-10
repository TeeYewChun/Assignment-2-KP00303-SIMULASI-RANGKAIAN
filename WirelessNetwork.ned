//Tee Yew Chun BI20110050
//Fong How Yan BI20110070
simple laptop
{
parameters:
@display("i=device/laptop");
gates:
input radioIn @directIn;
}

simple router
{
parameters:
@display("i=device/router");
gates:
input radioIn @directIn;
}


network WirelessNetwork
{
@display("bgb=418,284");
submodules:
Laptop1: laptop {
@display("p=65,88");
}

Laptop2: laptop {
@display("p=331,88");
}
Router: router {
@display("p=167,211");
}

}
