/* Question:
Implement regular expression matching with support for ‘.’ and ‘*’.

‘.’ Matches any single character.
‘*’ Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch(“aa”,”a”) -> false
isMatch(“aa”,”aa”) -> true
isMatch(“aaa”,”aa”) -> false
isMatch(“aa”, “a*”) -> true
isMatch(“aa”, “.*”) -> true
isMatch(“ab”, “.*”) -> true
isMatch(“aab”, “c*a*b”) -> true

reference: http://webcache.googleusercontent.com/search?q=cache:OECWAbO-vasJ:leetcode.com/2011/09/regular-expression-matching.html+&cd=1&hl=en&ct=clnk&gl=at

The recursion mainly breaks down elegantly to the following two cases:
1.) If the next character of p is NOT ‘*’, then it must match the current character of s. Continue 
pattern matching with the next character of both s and p.
2.) If the next character of p is ‘*’, then we do a brute force exhaustive matching of 0, 1, or more 
repeats of current character of p… Until we could not match any more characters.
*/

bool isMatch(const char *s, const char *p) {
    if (*p == '\0') return *s == '\0';
    
    // next char is '*'
    if (*(p+1) == '*') {
        while ((*s == *p) || (*s != '\0' && *p == '.')) {
            if(isMatch(s, p+2)) return true;
            s++;
        }
        return isMatch(s, p+2);
    // next char is not '*': must match current character
    } else (*(p+1) != '*') {
        return ((*s == *p) || (*s != '\0' && *p == '.')) && (isMatch(++s, ++p));
    }
}