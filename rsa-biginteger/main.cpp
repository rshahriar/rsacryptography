#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>

#define MILLIS 1000

using namespace std;

class BigInteger {
private:
    string number;
    bool sign;

public:
    BigInteger(); // empty constructor
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
    friend std::ostream& operator<<(std::ostream& out,BigInteger a);

private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);

    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<BigInteger, BigInteger> divide(BigInteger dividend, BigInteger divisor);

    string toString(long long n);
    long long toInt(string s);
};

//-----------------------------------------Implementation---------------------------------------------------------------
std::ostream& operator <<(std::ostream& out,BigInteger a) {
    out << a.getNumber();
    return out;
}


// modular exponentiation
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


// Miller-Rabin for Primality Testing
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
        BigInteger a = random % (p-1) + 1;

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


BigInteger generateRandomNumbers(int digit) {
    string s;

    for (int i =0; i< digit; i++) {
        string random =  BigInteger(rand()).getNumber();
        if (i == 0)
            s = random[0];
        else {
            s += random[1];
        }
    }

    return BigInteger(s);
}


bool fermatPrimalityTest(BigInteger p, int iterations) {
    if (p == 1 || p % 2 == 0) {
        return false;
    }

    for (int i = 0; i < iterations; i++) {
        BigInteger a = (BigInteger)rand() % (p - 1) + 1;
        if (modulo(a, p - 1, p) != 1){
            return false;
        }
    }

    return true;
}


// Generates Prime number of desired length By Fermat's Theorm
BigInteger generatePrimeWithFermat(int digit) {
    BigInteger n = generateRandomNumbers(digit);
    cout << n << endl;

    int breakVal = 0;
    while (fermatPrimalityTest(n, 10) == false) {
        n = generateRandomNumbers(digit);
        cout << n << endl;
        breakVal++;
        if (breakVal == 100)
            return 0;
    }

    return n;
}


// Generates Prime number of desired length
BigInteger generatePrimeWithMiller(BigInteger p) {
    while (!Miller(p, 5)) {
        p++;
    }
    return p;
}


//Calculates GCD
BigInteger gcd(BigInteger a, BigInteger b) {
    BigInteger temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


BigInteger gcdExtended(BigInteger a, BigInteger b, BigInteger *x, BigInteger *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    BigInteger x1, y1; // To store results of recursive call
    BigInteger gcd = gcdExtended(b, a%b, &x1, &y1);

    *x = y1;
    *y = x1 - (a/b) * y1;

    return gcd;
}


// Calculates D from e and N
BigInteger findD(BigInteger e, BigInteger N) {
    BigInteger k = 1;

    while (1) {
        k = k + N;
        if (k % e == 0) {
            return (k / e);
        }
    }
}


// Calculates E
BigInteger findE(BigInteger phiN) {
    BigInteger popularEvalues[6] = {3, 5, 7, 17, 257, 65537};
    for (int i = 0; i < 6; i++) {
        if (gcd (popularEvalues[i], phiN) == 1) {
            cout << "\nValue of e: " << popularEvalues[i];
            return popularEvalues[i];
        }
    }
    return 0;
}


// Message Encryption
BigInteger encryptMessage(BigInteger message, BigInteger e, BigInteger N) {
    const clock_t begin_time = clock();
    BigInteger en = modulo(message, e, N);
    cout<< "Encrypted message: " << en << endl;
    cout << "\nTime of encryption  = " << float( clock () - begin_time ) * MILLIS / CLOCKS_PER_SEC << " ms" << endl;
    return en;
}


// Message Decryption
void decryptMessage(BigInteger encryptedMsg, BigInteger d, BigInteger N) {
    const clock_t begin_time = clock();
    BigInteger de = modulo(encryptedMsg, d, N);
    cout<< "\nDecrypted message: " << de << endl;
    cout << "\nTime of decryption  = " << float( clock () - begin_time) * MILLIS / CLOCKS_PER_SEC << " ms" << endl;
}


int main() {
    string p, q;
    string bits;
    cout << "Fixed value of N: 1000 bit" << endl;

    // code for prime number generation will be done later
/*
    p = generatePrimeWithFermat(digits);
    cout <<"p: " << p << endl;

    q = generatePrimeWithFermat(digits);
    cout <<"q: " << q << endl;
*/

    // initiate prime number of 151 digits
    BigInteger b1("8290515735040856273279920028019754089906648110503848228748187375207350805510166301444321260999006754288859997100400526846118668190294438035469087208971");
    BigInteger b2("1201220374814320143127279864545495373815987095424121160482538063721483660688779311129370377018803872219275627461811376074607800016797301371429593867351");

    clock_t time_n = clock();

    BigInteger N = b1 * b2;
    cout <<"N: " << N << endl;
    cout << "\nTime to calculate N  = " << float( clock () - time_n ) * MILLIS /  CLOCKS_PER_SEC << " ms" <<endl;
    BigInteger phiN = (b1 - 1) * (b2 - 1);

    clock_t time_e = clock();
    BigInteger e = findE(phiN);
    cout << "\nTime to calculate e = " << float( clock () - time_e) * MILLIS /  CLOCKS_PER_SEC << " ms" << endl;

    clock_t time_d = clock();
    BigInteger d = findD(e, phiN);
    cout << "\nTime to calculate d  = " << float( clock () - time_d) * MILLIS /  CLOCKS_PER_SEC << " ms" << endl;
    cout << "\nd = " << d << endl;

    string input;
    cout << "\nEnter Message: " << endl;
    cin >> input;
    BigInteger message(input);
    BigInteger en = encryptMessage(message, e, N);
    decryptMessage(en, d, N);
    return 0;
}


//-------------------------------------- Constructor -----------------------------------------------------------
BigInteger::BigInteger() {
    number = "0";
    sign = false;
}


BigInteger::BigInteger(string s) {
    if( isdigit(s[0]) ) {
        setNumber(s);
        sign = false; // +ve
    } else {
        setNumber( s.substr(1) );
        sign = (s[0] == '-');
    }
}


BigInteger::BigInteger(string s, bool sin) {
    setNumber( s );
    setSign( sin );
}


BigInteger::BigInteger(int n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;

    if( isdigit(s[0]) ) {
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


const string& BigInteger::getNumber() {
    return number;
}


void BigInteger::setSign(bool s) {
    sign = s;
}


const bool& BigInteger::getSign() {
    return sign;
}


BigInteger BigInteger::absolute() {
    return BigInteger(getNumber());
}


//-------------------------------------- Operators ------------------------------------------------------------
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


BigInteger& BigInteger::operator ++() {
    (*this) = (*this) + 1;
    return (*this);
}


BigInteger BigInteger::operator ++(int) {
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}


BigInteger& BigInteger::operator --() {
    (*this) = (*this) - 1;
    return (*this);

}


BigInteger BigInteger::operator --(int) {
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
    if(addition.getNumber() == "0")
        addition.setSign(false);

    return addition;
}


BigInteger BigInteger::operator - (BigInteger b) {
    b.setSign( ! b.getSign() );
    return (*this) + b;
}


BigInteger BigInteger::operator * (BigInteger b) {
    BigInteger mul;

    mul.setNumber( multiply(getNumber(), b.getNumber() ) );
    mul.setSign( getSign() != b.getSign() );

    if(mul.getNumber() == "0")
        mul.setSign(false);

    return mul;
}


BigInteger BigInteger::operator / (BigInteger b) {
    BigInteger div;
    div = divide((*this), b).first;
    if(div.getNumber() == "0")
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


BigInteger BigInteger::operator -() {
    return (*this) * -1;
}


BigInteger::operator string() { // for conversion from BigInteger to string
    string signedString = ( getSign() ) ? "-" : "";
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
        return n1.getNumber().compare( n2.getNumber() ) > 0;
    }
}


bool BigInteger::greater(BigInteger n1, BigInteger n2) {
    return ! equals(n1, n2) && ! less(n1, n2);
}


string BigInteger::add(string number1, string number2) {
    string add = (number1.length() > number2.length()) ?  number1 : number2;
    char carry = '0';
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left
    else {
        number1.insert(0, differenceInLength, '0');
    }

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

    while(sub[0]=='0' && sub.length()!=1) {
        sub.erase(0,1);
    }

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

            temp[j] += '0';
        }

        if(carry > 0)
            temp.insert(0, 1, (carry+'0'));

        temp.append((n1.length()-i-1), '0');

        res = add(res, temp);
    }

    while(res[0] == '0' && res.length()!=1)
        res.erase(0,1);

    return res;
}


/*
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
*/


pair<BigInteger, BigInteger> BigInteger::divide(BigInteger dividend, BigInteger divisor) {
    // if we don't need to divide at all
    if (dividend < divisor) {
        return make_pair(BigInteger("0", dividend.getSign() != divisor.getSign()),
                         BigInteger(dividend, dividend.getSign() != divisor.getSign()));
    }

    BigInteger quotient = BigInteger("0", dividend.getSign() != divisor.getSign());
    BigInteger remainder = BigInteger(dividend.absolute());
    BigInteger divisorAbs = BigInteger(divisor.absolute());
    //int iterator = 0;
    while(remainder >= divisorAbs) {
        //iterator++;
        // check if divisor and remainder are equal sized, then quotient should be less than 10
        if (remainder.getNumber().length() == divisorAbs.getNumber().length()) {
            // if equal sized then calculate the division by subtraction, less than 10 subtracts
            while (remainder >= divisorAbs) {
                remainder -= divisorAbs;
                quotient++;
            }
        } else {
            // if not equal sized then project a close multiple of the divisor to dividend by multiplying 10's
            BigInteger temp = BigInteger(remainder.getNumber().substr(0, divisorAbs.getNumber().length()));
            long numberOfZeros = 0;
            // check if multiplying 10's to divisor will generate a bigger number than dividend
            int tempRatio = 0;
            if (temp >= divisorAbs) {
                // now 10's multiple will be less than or equal to dividend
                numberOfZeros = remainder.getNumber().length() - divisorAbs.getNumber().length();
                while (temp >= divisorAbs) {
                    temp -= divisorAbs;
                    tempRatio++;
                }
            } else {
                // multiply 10's 1 less to generate a number that is less than dividend
                numberOfZeros = remainder.getNumber().length() - divisorAbs.getNumber().length() - 1;
                string str = temp.getNumber();
                str.append(1, '0');
                temp = BigInteger(str);
                while (temp >= divisorAbs) {
                    temp -= divisorAbs;
                    tempRatio++;
                }
            }

            string qStr("");
            qStr.append(1, '0' + tempRatio);
            qStr.append(numberOfZeros, '0');
            quotient += BigInteger(qStr);

            BigInteger surplusDivisor = divisorAbs * tempRatio;
            string tempDivisorStr = surplusDivisor.getNumber();
            tempDivisorStr.append(numberOfZeros, '0');
            remainder -= BigInteger(tempDivisorStr);
        }
    }

    return make_pair(quotient, remainder);
};
