//
// Created by Sereg on 26.11.2019.
//

void testaddress()
{
    string A, B;
    cout << "Введіть Мережу\n"; cin>>A ;
    cout << "Введіть Адресу\n"; cin>>B;

    cout<< A << " & " << B << " = " << Network(A).test(Address(B));
    cout<<endl<<endl;

    cout << "2001:0db8:abcd:0013:0000:0000:0000:0000 in 2001:db8:abcd:12:0:0:0:0/64 = ";
    cout << Network("2001:db8:abcd:12:0:0:0:0/64").test(Address("2001:0db8:abcd:0013:0000:0000:0000:0000"));
    cout << endl;

}