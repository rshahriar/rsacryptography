/*
 * @author panks
 * Big Integer library in C++, single file implementation.
 */
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#define MAX 10000 // for strings

using namespace std;
class BigInteger {
private:
    string number;
    bool sign;
public:
    BigInteger(); // empty constructor initializes zero
    BigInteger(string s); // "string" constructor
    BigInteger(string s, bool sin); // "string" constructor
    BigInteger(int n); // "int" constructor
    void setNumber(string s);
    const string& getNumber(); // retrieves the number
    void setSign(bool s);
    const bool& getSign();
    BigInteger absolute(); // returns the absolute value
    void operator = (BigInteger b);
    bool operator == (BigInteger b);
    bool operator != (BigInteger b);
    bool operator > (BigInteger b);
    bool operator < (BigInteger b);
    bool operator >= (BigInteger b);
    bool operator <= (BigInteger b);
    BigInteger& operator ++(); // prefix
    BigInteger  operator ++(int); // postfix
    BigInteger& operator --(); // prefix
    BigInteger  operator --(int); // postfix
    BigInteger operator + (BigInteger b);
    BigInteger operator - (BigInteger b);
    BigInteger operator * (BigInteger b);
    BigInteger operator / (BigInteger b);
    BigInteger operator % (BigInteger b);
    BigInteger& operator += (BigInteger b);
    BigInteger& operator -= (BigInteger b);
    BigInteger& operator *= (BigInteger b);
    BigInteger& operator /= (BigInteger b);
    BigInteger& operator %= (BigInteger b);
    BigInteger& operator [] (int n);
    BigInteger operator -(); // unary minus sign
    operator string(); // for conversion from BigInteger to string
private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
//    pair<BigInteger, BigInteger> divide(BigInteger dividend, BigInteger divisor);
    pair<BigInteger, BigInteger> divide(BigInteger dividend, BigInteger divisor);
    pair<BigInteger, BigInteger> divideSurplus(BigInteger dividend, BigInteger divisor);
//    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};

/*

 * modular exponentiation

 */

BigInteger modulo(BigInteger base, BigInteger exponent, BigInteger mod) {
    BigInteger x = 1;
    BigInteger y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

BigInteger mulmod(BigInteger a, BigInteger b, BigInteger mod) {
    BigInteger x = 0,y = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

bool Miller(BigInteger p, int iteration) {
    if (p < 2) {
        return false;
    }

    if (p != 2 && p % 2==0) {
        return false;
    }

    BigInteger s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++) {
        BigInteger random = (BigInteger)rand();
        BigInteger pLess = p - 1;
        BigInteger a = random % pLess;
        a = a + 1;
        BigInteger temp = s;
        BigInteger mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
//    BigInteger b1("10090000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001013000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010210000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001031");
    BigInteger b1("1814159566819970307982681716822107016038920170504391457462563485198126916735167260215619523429714031");
//    BigInteger b1("7212610147295474909544523785043492409969382148186765460082500085393519556525921455588705423020751421");
    const clock_t begin_time = clock();
    if (Miller(b1, 10)) {
        std::cout << "The number is prime!";
    }
//    std::cout << (b1 % 2).getNumber();
    std::cout << "\nTime taken to perform primality test  = " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    return 0;
}



//------------------------------------------------------------------------------

BigInteger::BigInteger() { // empty constructor initializes zero
    number = "0";
    sign = false;
}

BigInteger::BigInteger(string s) { // "string" constructor
    if( isdigit(s[0]) ) { // if not signed
        setNumber(s);
        sign = false; // +ve
    } else {
        setNumber( s.substr(1) );
        sign = (s[0] == '-');
    }
}

BigInteger::BigInteger(string s, bool sin) { // "string" constructor
    setNumber( s );
    setSign( sin );
}

BigInteger::BigInteger(int n) { // "int" constructor
    stringstream ss;
    string s;
    ss << n;
    ss >> s;


    if( isdigit(s[0]) ) { // if not signed
        setNumber( s );
        setSign( false ); // +ve
    } else {
        setNumber( s.substr(1) );
        setSign( s[0] == '-' );
    }
}

void BigInteger::setNumber(string s) {
    number = s;
}

const string& BigInteger::getNumber() { // retrieves the number
    return number;
}

void BigInteger::setSign(bool s) {
    sign = s;
}

const bool& BigInteger::getSign() {
    return sign;
}

BigInteger BigInteger::absolute() {
    return BigInteger( getNumber() ); // +ve by default
}

void BigInteger::operator = (BigInteger b) {
    setNumber( b.getNumber() );
    setSign( b.getSign() );
}

bool BigInteger::operator == (BigInteger b) {
    return equals((*this) , b);
}

bool BigInteger::operator != (BigInteger b) {
    return ! equals((*this) , b);
}

bool BigInteger::operator > (BigInteger b) {
    return greater((*this) , b);
}

bool BigInteger::operator < (BigInteger b) {
    return less((*this) , b);
}

bool BigInteger::operator >= (BigInteger b) {
    return equals((*this) , b)
           || greater((*this), b);
}

bool BigInteger::operator <= (BigInteger b) {
    return equals((*this) , b)
           || less((*this) , b);
}

BigInteger& BigInteger::operator ++() { // prefix
    (*this) = (*this) + 1;
    return (*this);
}

BigInteger BigInteger::operator ++(int) { // postfix
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}

BigInteger& BigInteger::operator --() { // prefix
    (*this) = (*this) - 1;
    return (*this);

}

BigInteger BigInteger::operator --(int) { // postfix
    BigInteger before = (*this);
    (*this) = (*this) - 1;
    return before;
}

BigInteger BigInteger::operator + (BigInteger b) {
    BigInteger addition;
    if( getSign() == b.getSign() ) { // both +ve or -ve
        addition.setNumber( add(getNumber(), b.getNumber() ) );
        addition.setSign( getSign() );
    } else { // sign different
        if( absolute() > b.absolute() ) {
            addition.setNumber( subtract(getNumber(), b.getNumber() ) );
            addition.setSign( getSign() );
        } else {
            addition.setNumber( subtract(b.getNumber(), getNumber() ) );
            addition.setSign( b.getSign() );
        }
    }
    if(addition.getNumber() == "0") // avoid (-0) problem
        addition.setSign(false);

    return addition;
}

BigInteger BigInteger::operator - (BigInteger b) {
    b.setSign( ! b.getSign() ); // x - y = x + (-y)
    return (*this) + b;
}

BigInteger BigInteger::operator * (BigInteger b) {
    BigInteger mul;

    mul.setNumber( multiply(getNumber(), b.getNumber() ) );
    mul.setSign( getSign() != b.getSign() );

    if(mul.getNumber() == "0") // avoid (-0) problem
        mul.setSign(false);

    return mul;
}

BigInteger BigInteger::operator / (BigInteger b) {
    BigInteger div;
    div = divide((*this), b).first;
    if(div.getNumber() == "0") // avoid (-0) problem
        div.setSign(false);
    return div;
}

BigInteger BigInteger::operator % (BigInteger b) {
    if (b == 2) {
        string number = (*this).getNumber();
        int lastDigit = number[number.length()-1] - '0';
        if (lastDigit==0 || lastDigit==2 || lastDigit==4 || lastDigit==6 || lastDigit==8) {
            return BigInteger("0", (*this).getSign() != b.getSign());
        } else {
            return BigInteger("1", (*this).getSign() != b.getSign());
        }
    } else {
        BigInteger rem = divide((*this), b).second;
        return rem;
    }
}

BigInteger& BigInteger::operator += (BigInteger b) {
    (*this) = (*this) + b;
    return (*this);
}

BigInteger& BigInteger::operator -= (BigInteger b) {
    (*this) = (*this) - b;
    return (*this);
}

BigInteger& BigInteger::operator *= (BigInteger b) {
    (*this) = (*this) * b;
    return (*this);
}

BigInteger& BigInteger::operator /= (BigInteger b) {
    (*this) = (*this) / b;
    return (*this);
}

BigInteger& BigInteger::operator %= (BigInteger b) {
    (*this) = (*this) % b;
    return (*this);
}

BigInteger& BigInteger::operator [] (int n) {
    return *(this + (n*sizeof(BigInteger)));
}

BigInteger BigInteger::operator -() { // unary minus sign
    return (*this) * -1;
}

BigInteger::operator string() { // for conversion from BigInteger to string
    string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
    signedString += number;
    return signedString;
}

bool BigInteger::equals(BigInteger n1, BigInteger n2) {
    return n1.getNumber() == n2.getNumber()
           && n1.getSign() == n2.getSign();
}

bool BigInteger::less(BigInteger n1, BigInteger n2) {
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if(! sign1 && sign2)
        return false;

    else if(! sign1) { // both +ve
        if(n1.getNumber().length() < n2.getNumber().length() )
            return true;
        if(n1.getNumber().length() > n2.getNumber().length() )
            return false;
        return n1.getNumber() < n2.getNumber();
    } else { // both -ve
        if(n1.getNumber().length() > n2.getNumber().length())
            return true;
        if(n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
    }
}

bool BigInteger::greater(BigInteger n1, BigInteger n2) {
    return ! equals(n1, n2) && ! less(n1, n2);
}

string BigInteger::add(string number1, string number2) {
    string add = (number1.length() > number2.length()) ?  number1 : number2;
    char carry = '0';
    int differenceInLength = abs( (int) (number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else// if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.size()-1; i>=0; --i) {
        add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

        if(i != 0) {
            if(add[i] > '9') {
                add[i] -= 10;
                carry = '1';
            } else
                carry = '0';
        }
    }
    if(add[0] > '9') {
        add[0]-= 10;
        add.insert(0,1,'1');
    }
    return add;
}

string BigInteger::subtract(string number1, string number2) {
    string sub = (number1.length()>number2.length())? number1 : number2;
    int differenceInLength = abs( (int)(number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.length()-1; i>=0; --i) {
        if(number1[i] < number2[i]) {
            number1[i] += 10;
            number1[i-1]--;
        }
        sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
    }

    while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
        sub.erase(0,1);

    return sub;
}

string BigInteger::multiply(string n1, string n2) {
    if(n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for(int i=n1.length()-1; i>=0; --i) {
        string temp = n2;
        int currentDigit = n1[i]-'0';
        int carry = 0;

        for(int j=temp.length()-1; j>=0; --j) {
            temp[j] = ((temp[j]-'0') * currentDigit) + carry;

            if(temp[j] > 9) {
                carry = (temp[j]/10);
                temp[j] -= (carry*10);
            } else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if(carry > 0)
            temp.insert(0, 1, (carry+'0'));

        temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add(res, temp); // O(n)
    }

    while(res[0] == '0' && res.length()!=1) // erase leading zeros
        res.erase(0,1);

    return res;
}

/*
pair<BigInteger, BigInteger> BigInteger::divide(BigInteger dividend, BigInteger divisor) {
    // handle special case for 2, ends with a even number
    // handle special case for 3, sum of all numbers divisible by 3
    BigInteger zero("0");
    BigInteger remainder(dividend.getNumber());
    BigInteger quotient("0");
    while (remainder >= divisor) {
        remainder -= divisor;
        quotient++;
    }
    if (dividend.getSign() != divisor.getSign()) {
        quotient.setSign(true);
        remainder.setSign(true);
    }
    return make_pair(quotient, remainder);
}
*/

pair<BigInteger, BigInteger> BigInteger::divide(BigInteger dividend, BigInteger divisor) {

    // if we don't need to divide at all
    if (dividend < divisor) {
        return make_pair(BigInteger("0", dividend.getSign() != divisor.getSign()),
                         BigInteger(dividend, dividend.getSign() != divisor.getSign()));
    }

    BigInteger quotient = BigInteger("0");
    BigInteger remainder = BigInteger(dividend);
    while(remainder >= divisor) {
        // check if divisor and remainder are equal sized, then quotient should be less than 10
        if (remainder.getNumber().length() == divisor.getNumber().length()) {
            // if equal sized then calculate the division by subtraction, less than 10 subtracts
            while (remainder >= divisor) {
                remainder -= divisor;
                quotient++;
            }
        } else {
            // if not equal sized then project a close multiple of the divisor to dividend by multiplying 10's
            BigInteger temp = BigInteger(remainder.getNumber().substr(0, divisor.getNumber().length()));
            long numberOfZeros = 0;
            // check if multiplying 10's to divisor will generate a bigger number than dividend
            if (temp >= divisor.absolute()) {
                // now 10's multiple will be less than or equal to dividend
                numberOfZeros = remainder.getNumber().length() - divisor.getNumber().length();
            } else {
                // multiply 10's 1 less to generate a number that is less than dividend
                numberOfZeros = remainder.getNumber().length() - divisor.getNumber().length() - 1;
            }

            string qStr = "1";
            qStr.append(numberOfZeros, '0');
            quotient += BigInteger(qStr);

            string tempDivisorStr = divisor.getNumber();
            tempDivisorStr.append(numberOfZeros, '0');
            remainder -= BigInteger(tempDivisorStr);
        }
    }
    return make_pair(quotient, remainder);
}

pair<BigInteger, BigInteger> BigInteger::divideSurplus(BigInteger dividend, BigInteger divisor) {
    // if we don't need to divide at all
    if (dividend < divisor) {
        return make_pair(BigInteger("0", dividend.getSign() != divisor.getSign()),
                         BigInteger(dividend, dividend.getSign() != divisor.getSign()));
    }

    BigInteger quotient = BigInteger("0");
    BigInteger remainder = BigInteger(dividend);
    BigInteger divisorAbs = divisor.absolute();

    while(remainder >= divisor) {
        // check if divisor and remainder are equal sized, then quotient should be less than 10
        if (remainder.getNumber().length() == divisor.getNumber().length()) {
            // if equal sized then calculate the division by subtraction, less than 10 subtracts
            while (remainder >= divisor) {
                remainder -= divisor;
                quotient++;
            }
        } else {
            // if not equal sized then project a close multiple of the divisor to dividend by multiplying 10's
            BigInteger temp = BigInteger(remainder.getNumber().substr(0, divisor.getNumber().length()));
            long numberOfZeros = 0;
            // check if multiplying 10's to divisor will generate a bigger number than dividend
            int surplus = 0;
            if (temp >= divisorAbs) {
                // now 10's multiple will be less than or equal to dividend
                numberOfZeros = remainder.getNumber().length() - divisor.getNumber().length();
                while (temp >= divisorAbs) {
                    temp -= divisorAbs;
                    surplus++;
                }
            } else {
                // multiply 10's 1 less to generate a number that is less than dividend
                numberOfZeros = remainder.getNumber().length() - divisor.getNumber().length() - 1;
                int remainderFirstDigit = remainder.getNumber()[0] - '0';
                int divisorFirstDigit = divisorAbs.getNumber()[0] - '0';
                surplus = remainderFirstDigit * 10 / divisorFirstDigit;
            }

            string qStr("");
            qStr.append(1, '0' + surplus);
            qStr.append(numberOfZeros, '0');
            quotient += BigInteger(qStr);

            BigInteger surplusDivisor = divisor * surplus;
            string tempDivisorStr = surplusDivisor.getNumber();
            tempDivisorStr.append(numberOfZeros, '0');
            remainder -= BigInteger(tempDivisorStr);
        }
    }
    return make_pair(quotient, remainder);
};

string BigInteger::toString(long long n) {
    stringstream ss;
    string temp;

    ss << n;
    ss >> temp;

    return temp;
}

long long BigInteger::toInt(string s) {
    long long sum = 0;

    for(int i=0; i<s.length(); i++)
        sum = (sum*10) + (s[i] - '0');

    return sum;
}

