#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdlib>
#define MAX(x, y) ((x) > (y) ? (x) : (y))
using namespace std;
class GM {
public:
    static double getRandomNumberFromTheInterval(double left, double right) {
        return ((double)rand() * (right - left)) / RAND_MAX + left;
    }
    static double exponentialDistribution(double upperBorder, double lambda) {
        if (upperBorder < 0)
            return 0;
        return 1 - exp(-upperBorder * lambda);
    }
    static double inverseExponentialDistribution(double exponentialDistributionValue, double lambda) {
        return -log(exponentialDistributionValue) / lambda;
    }
    static double distributionDencity(double x, double lambda){ return lambda * exp (- lambda * x);}
};

class VX {
    priority_queue<double> q;
    double l;

public:
    VX(double lambda) : l(lambda) {};

    void setX(double u) {
        if (u < 0 || u > 1)
            throw("Incorrect value");
        q.push(GM::inverseExponentialDistribution(u, l));
    }

    vector<double> getVs(void) {
        vector<double> v(q.size());
        priority_queue<double> tmp(q);
        
        while (!tmp.empty()) {
            v[tmp.size() - 1] = tmp.top();
            tmp.pop();
        }
        return v;
    }
    size_t getNumberOfMS(double left, double right) {
        priority_queue<double> qq(q);
        size_t tmp = 0;
        while (!qq.empty() && qq.top() < left) qq.pop();
        while (!qq.empty() && qq.top() < right) { tmp++; qq.pop(); }
        return tmp;
    }

};

VX generateXs(size_t n, double lambda);

class NC {
    
public:
    NC(void) {};
    NC(VX vx, double lambda) : v(vx.getVs()), l(lambda) {};
    NC(double lambda, size_t n){ v = generateXs(n, lambda).getVs(); l = lambda;}
    NC(const vector<double>& vv, double lambda) : v(vv), l(lambda) {}
    NC(const NC& nc) : v(nc.v), l(nc.l) {}
    ~NC(void) {}

    void setXs(VX vx) { v = vx.getVs(); }
    void setLambda(double lambda) { l = lambda; }

    double median(void) { size_t t = v.size() / 2; return v.size() % 2 ? v[t + 1] : (v[t] + v[t + 1]) / 2;}
    double avg(void) {double res = 0; for(double x : v) res += x; return res / v.size();}
    double Vdispercion(void) {double a = avg(), res = 0; for(double x : v) res += pow(x - a, 2); return res / v.size();}
    double range(void) {return v.back() - v.front();}

    double fEta(double x) { size_t res = 0; 
        for (size_t i = 0; i < v.size() && v[i] < x; i++) 
            res += 1; 
            return res / v.size();}

    double theordispercion(void) {return 1 / pow(l, 2);}
    double mathexp(void) {return 1 / l;}
    double D (void) { 
        size_t n = v.size();
        double max;
        for (size_t i = 0; i < n; i++){
            max = MAX((double)(i+1)/n - GM::exponentialDistribution(v[i], l),
                GM::exponentialDistribution(v[i], l) - (double)i/n);
        }
        return max;
    }
private:
    vector<double> v;
    double l;
};

class INTERVALS {
public:
    INTERVALS(void) {}
    ~INTERVALS(void) {}
    void setBorder(double x) { v.push_back(x);} //пихаем разрезы x > 0 должен быть
    vector<double> getZis(void) {
        sort(v.begin(), v.end());
        vector<double> res;
        res.push_back(v.front() / 2);
        for (size_t i = 0, j = 1; j < v.size(); i++, j++) {
            res.push_back((v[j] + v[i]) / 2);
        }
        res.push_back((double)INFINITY);
        return res;
    }

    vector<double> histogram(VX vx) {
        vector<double> h;
        h.push_back(vx.getNumberOfMS(0, v.front()));
        for (size_t i = 0, j = 1; j < v.size(); i++, j++) {
            h.push_back(vx.getNumberOfMS(v[i], v[j]));
        }
        h.push_back(vx.getNumberOfMS(v.back(), vx.getVs().back() + 0.000001));
    }
private:
    vector<double> v;
};
