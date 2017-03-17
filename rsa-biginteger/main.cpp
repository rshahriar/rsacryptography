#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
//#define MAX 10000 // for strings

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
    friend std::ostream& operator<<(std::ostream& out,BigInteger a);

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
    pair<BigInteger, BigInteger> divideSquaredProjection(BigInteger dividend, BigInteger divisor);
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

BigInteger gcd(BigInteger a, BigInteger b) {
    BigInteger temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


BigInteger gcdExtended(BigInteger a, BigInteger b, BigInteger *x, BigInteger *y)
{
    // Base Case
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    BigInteger x1, y1; // To store results of recursive call
    BigInteger gcd = gcdExtended(b, a%b, &x1, &y1);

    // Update x and y using results of recursive
    // call

    *x = y1;
    *y = x1 - (a/b) * y1;


    return gcd;
}

BigInteger calculate_d(BigInteger x, BigInteger t)
{
    BigInteger k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

BigInteger findE(BigInteger phiN) {
    BigInteger popularEvalues[5] = {3, 7, 17, 257, 65537};
    for (int i = 0; i < 5; i++) {
        if (gcd (popularEvalues[i], phiN) == 1) {
            return popularEvalues[i];
        }
    }

    return 0;
}


std::ostream& operator <<(std::ostream& out,BigInteger a)
{
    out << a.getNumber();
    return out;
}

int main() {
/*
//    BigInteger b1("1814159566819970307982681716822107016038920170504391457462563485198126916735167260215619523429714031");

    BigInteger b1("10090000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001013000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010210000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001031");
    BigInteger b2("721261014729547490954452378504349240996938214818676546008250008539351955652592145558870542302075142100000");
//    BigInteger b1("787345");
//    BigInteger b2("123");
    BigInteger b3 = b1 / b2;
    const clock_t begin_time = clock();
    cout<< b3.getNumber();
    cout << "\nTime taken for b1 / b2 = " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
*/

//    if (Miller(b2, 10)) {
//        std::cout << "The number is prime!";
//    }

    BigInteger b1("2071561667400245712088091542256908512206470131429679791728284604628489949383382852054263725446770019431856265272566210206028080915537623664508293339218888855829741302772372696799198697890193514567953840554756498581501030028732877786636129759291825384798494860219898397736829391041740868492459331514262769204776882413720166875829386657690097056328122106147523284369357662710052860991083760187090058216260432280354147365325944143590324309806584380567448454116167669");
    BigInteger b2("1912401190856324558608863437762526732142183429695085360631093911123770848507956265834176055433948346689923354607444585226608201263265775574369423255238079257584120915498808287374862118195634864322724516060054753867489543157037865371366807450685864574809585321827884246842788781492944665460872779599494214438240713259304779633449548698479375269475955753823879878151057005679051049895949889676841685448036465386999184327834831481335146129830037079064509960244134533");
    BigInteger x, y;
    BigInteger a, b = (b1 - 1) * (b2 - 1);
    a = findE(b);

    BigInteger message("7845737565212109");

    const clock_t begin_time = clock();
    BigInteger en = modulo(message, a, (b1 * b2));
    cout<< "en is " << en << endl;
    cout << "\nTime taken to claculate en  = " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;

    const clock_t begin_time1 = clock();
    BigInteger d = calculate_d(a, b);
    cout << "\nTime taken to claculate d  = " << float( clock () - begin_time1 ) /  CLOCKS_PER_SEC;

    const clock_t begin_time2 = clock();
    BigInteger de = modulo(en, d, (b1 * b2));
    cout<< "\nde is " << de << endl;
    cout << "\nTime taken to calculate de  = " << float( clock () - begin_time2 ) /  CLOCKS_PER_SEC << endl;

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
    long ratio = (*this).getNumber().length()/b.getNumber().length();
/*
    if (ratio < 2) {
        div = divideSurplus((*this), b).first;
    } else if (ratio >= 2) {
        div = divideSquaredProjection((*this), b).first;
    }
*/
    div = divide((*this), b).first;
    if(div.getNumber() == "0") // avoid (-0) problem
        div.setSign(false);
    return div;
}

BigInteger BigInteger::operator % (BigInteger b) {
    // use number properties to reduce time complexity
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


pair<BigInteger, BigInteger> BigInteger::divide(BigInteger dividend, BigInteger divisor) {

    BigInteger absoluteDividend = dividend.absolute();
    BigInteger absoluteDivisor = divisor.absolute();
    if (absoluteDividend < absoluteDivisor) {
        return make_pair(BigInteger("0", dividend.getSign() != divisor.getSign()),
                        BigInteger(dividend.getNumber(), dividend.getSign() != divisor.getSign()));
    }
    else if (absoluteDividend.getNumber().length() <= absoluteDivisor.getNumber().length() + 1) {
        BigInteger quotient("0");
        while (absoluteDividend >= absoluteDivisor) {
            absoluteDividend -= absoluteDivisor;
            quotient++;
        }
        return make_pair(BigInteger(quotient.getNumber(), dividend.getSign() != divisor.getSign()),
                         absoluteDividend);
    } else {

        unsigned long offset = absoluteDivisor.getNumber().length();
        string quotientStr = "";
        string remainderStr = "";
        string tempStr = absoluteDividend.getNumber().substr(0, offset);
        BigInteger temp = BigInteger(tempStr);

        //if we need to borrow from the very first time
        if (absoluteDivisor > temp) {
            ++offset;
            tempStr = absoluteDividend.getNumber().substr(0, offset);
            temp = BigInteger(tempStr);
        }

        while (absoluteDividend.getNumber().length() >= offset) {
            int q = 0;
            while (temp >= absoluteDivisor) {
                temp -= absoluteDivisor;
                q++;
            }
            // add q to quotient
            quotientStr.append(1, (char) ('0' + q));

            // make temp and divisor have equal number of digits
            unsigned long deficit = absoluteDivisor.getNumber().length() - temp.getNumber().length();
            tempStr.clear();
            tempStr.append(temp.getNumber());
            // looking ahead - not enough digits left
            if (offset + deficit > absoluteDividend.getNumber().length()) {
                remainderStr.append(tempStr);
                remainderStr.append(absoluteDividend.getNumber().substr(offset));
                break;
            }
            for (int i = 0; i < deficit; ++i) {
                tempStr.append(1, absoluteDividend.getNumber()[offset]);
                if (i >= 1) {
                    quotientStr.append(1, '0');
                }
                offset++;
            }
            temp = BigInteger(tempStr);

            if (absoluteDivisor > temp) {
                // we still need to borrow 1 digit from dividend
                // But can we?
                if (offset < absoluteDividend.getNumber().length()) {
                    tempStr.append(1, absoluteDividend.getNumber()[offset]);
                    temp = BigInteger(tempStr);
                    // stuff zeros to quotient
                    if (deficit >= 1) {
                        quotientStr.append(1, '0');
                    }
                    ++offset;
                } else {
                    // cannot borrow anymore from dividend - so, finish up
                    remainderStr = tempStr;
                    break;
                }
            }
        }
        return make_pair(BigInteger(quotientStr, dividend.getSign() != dividend.getSign()),
                            BigInteger(remainderStr, dividend.getSign() != dividend.getSign()));
    }
}

pair<BigInteger, BigInteger> BigInteger::divideSurplus(BigInteger dividend, BigInteger divisor) {
    // if we don't need to divide at all
    if (divisor == 1) {
        return make_pair(BigInteger(dividend, dividend.getSign() != divisor.getSign()),
                         BigInteger("0", dividend.getSign() != divisor.getSign()));
    }
    if (dividend < divisor) {
        return make_pair(BigInteger("0", dividend.getSign() != divisor.getSign()),
                         BigInteger(dividend, dividend.getSign() != divisor.getSign()));
    }

    BigInteger quotient = BigInteger("0", dividend.getSign() != divisor.getSign());
    BigInteger remainder = BigInteger(dividend.absolute());
    BigInteger divisorAbs = BigInteger(divisor.absolute());

    long iteration = 0;

    while(remainder >= divisorAbs) {
        iteration++;
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
            int surplus = 0;
            if (temp >= divisorAbs) {
                // now 10's multiple will be less than or equal to dividend
                numberOfZeros = remainder.getNumber().length() - divisorAbs.getNumber().length();
                while (temp >= divisorAbs) {
                    temp -= divisorAbs;
                    surplus++;
                }
            } else {
                // multiply 10's 1 less to generate a number that is less than dividend
                numberOfZeros = remainder.getNumber().length() - divisorAbs.getNumber().length() - 1;
                string str = temp.getNumber();
                str.append(1, '0');
                temp = BigInteger(str);
                while (temp >= divisorAbs) {
                    temp -= divisorAbs;
                    surplus++;
                }
            }

            string qStr("");
            qStr.append(1, '0' + surplus);
            qStr.append(numberOfZeros, '0');
            quotient += BigInteger(qStr);

            BigInteger surplusDivisor = divisorAbs * surplus;
            string tempDivisorStr = surplusDivisor.getNumber();
            tempDivisorStr.append(numberOfZeros, '0');
            remainder -= BigInteger(tempDivisorStr);
        }
    }
    cout<< "\nDividend=" << dividend.getNumber();
    cout<< "\nDivisor=" << divisor.getNumber();
    cout<< "\nIterations=" << iteration;
    return make_pair(quotient, remainder);
}

pair<BigInteger, BigInteger> BigInteger::divideSquaredProjection(BigInteger dividend, BigInteger divisor) {
/*
    BigInteger absoluteDivisor = divisor.absolute();
    BigInteger absoluteDividend = dividend.absolute();
    BigInteger projectedInteger = divisor.absolute();
    BigInteger quotient = BigInteger("0");
    while (dividend.getNumber().length() - projectedInteger.getNumber().length() >= divisor.getNumber().length()) {
        projectedInteger *= absoluteDivisor;
        quotient += absoluteDivisor;
    }
    if (projectedInteger > absoluteDividend) {
        while (projectedInteger >= absoluteDividend) {
            projectedInteger -= absoluteDivisor;
            quotient--;
        }
    }
    if (projectedInteger == absoluteDividend) {
        return make_pair(BigInteger(quotient.getNumber(), dividend.getSign() != divisor.getSign()), BigInteger("0"));
    }

    return pair<BigInteger, BigInteger>();
*/

    BigInteger absoluteDivisor = divisor.absolute();
    BigInteger absoluteDividend = dividend.absolute();
    BigInteger remainder = BigInteger(absoluteDividend);
    BigInteger quotient("0");
    while (remainder >= absoluteDivisor) {
        string projStr = "";
        projStr.append(remainder.getNumber().length() - divisor.getNumber().length() - 1, '9');
        quotient = BigInteger(projStr);
        BigInteger projectionBigInt = quotient * absoluteDivisor;
        BigInteger remainder = absoluteDividend - projectionBigInt;
    }
    return make_pair(BigInteger(quotient.getNumber(), dividend.getSign() != divisor.getSign()), remainder);
}

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