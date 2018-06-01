#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BigNumber
{
private:
   string input;
   vector<int> number;
   vector<int> newNumber;

public:
   BigNumber(string s)
   {
      input = s;
      for (int i = 0; i < s.size(); ++i)
      {
         number.push_back(input[i] - '0');
      }
   }
   void setString(string s)
   {
      input = s;
   }
   string getString()
   {
      return input;
   }
   void print()
   {
      for(int i = 0; i < number.size(); i++)
      {
         cout << number[i];
      }
      cout << endl;
   }

   friend void operator +(BigNumber &a, BigNumber& b)
   {
      reverse(a.number.begin(), a.number.end());
      reverse(b.number.begin(), b.number.end());

      int n1 = a.number.size();
      int n2 = b.number.size();

      if(n1 > n2)
      {
         a.number.swap(b.number);
         n1 = a.number.size();
         n2 = b.number.size();
      }

      vector<int> newNumber2;

      int carry = 0;
      for (int i=0; i<n1; i++)
      {

         int sum = ((a.number[i])+(b.number[i])+carry);
         newNumber2.push_back(sum%10);

         carry = sum / 10;
      }

      for (int i=n1; i<n2; i++)
      {
         int sum = ((b.number[i])+carry);
         newNumber2.push_back(sum%10);
         carry = sum / 10;
      }

      if (carry)
         newNumber2.push_back(carry);

      reverse(newNumber2.begin(), newNumber2.end());

      a.number.swap(newNumber2);

   }

   friend void operator -(BigNumber &a, BigNumber& b)
   {
      reverse(a.number.begin(), a.number.end());
      reverse(b.number.begin(), b.number.end());

      int n1 = a.number.size();
      int n2 = b.number.size();

      if(n1 < n2)
      {
         a.number.swap(b.number);
         n1 = a.number.size();
         n2 = b.number.size();
      }

      vector<int> newNumber2;

      int carry = 0;
      for (int i=0; i<n2; i++)
       {

          int sub = ((a.number[i])-(b.number[i])-carry);

          if (sub < 0)
          {
             sub = sub + 10;
             carry = 1;
          }
          else
            carry = 0;

         newNumber2.push_back(sub);
      }

      for (int i=n2; i<n1; i++)
      {
         int sub = ((a.number[i]) - carry);

         if (sub < 0)
         {
            sub = sub + 10;
            carry = 1;
         }
         else
            carry = 0;

         newNumber2.push_back(sub);
      }

      reverse(newNumber2.begin(), newNumber2.end());

      a.number.swap(newNumber2);
   }

   friend void operator *(BigNumber &a, BigNumber& b)
   {
      int n1 = a.number.size();
      int n2 = b.number.size();

      vector<int> result(n1 + n2, 0);

      int i_n1 = 0;
      int i_n2 = 0;

      for(int i = n1 - 1; i >= 0; i--)
      {
         int carry = 0;
         int n1 = a.number[i];

         i_n2 = 0;

         for (int j=n2-1; j>=0; j--)
         {
            int n2 = b.number[j];

            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            carry = sum/10;

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
         }

         if (carry > 0)
            result[i_n1 + i_n2] += carry;

         i_n1++;
      }
      int i = result.size() - 1;
      while (i>=0 && result[i] == 0)
      {
         i--;
      }

      reverse(result.begin(), result.end());

      a.number.swap(result);

   }

   /*BigNumber operator /(BigNumber other)
   {
      BigNumber q, r;
      q.a.resize(a.a.size());

      for (int i = a.a.size() - 1; i >= 0; i--) {
          r *= base;
          r += a.a[i];
          int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
          int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
          int d = ((long long) base * s1 + s2) / b.a.back();
          r -= b * d;
          while (r < 0)
             r += b, --d;
          q.a[i] = d;
      }
   }*/

   friend void operator %(BigNumber &a, int b)
   {
      int res = 0;

      for(int i = 0; i < a.number.size(); i++)
      {
         res = (res * 10 + a.number[i]) % b;
      }

      cout << res << endl;
   }


};
