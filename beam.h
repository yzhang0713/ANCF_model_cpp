#ifndef ANCF_MODEL_C___BEAM_H
#define ANCF_MODEL_C___BEAM_H
#include <Eigen/Dense>
#include <iostream>
#include "beam_forces.h"

using namespace std;
using namespace Eigen;

class beam {
private:
    double E = 8.0e8;               // Young's modulus (Pa)
    double rho = 8.5e2;             // Density (kg/m^3)
    double length = 1.0;          // Length of beam (m)
    double thick = 5.0e-4;           // Thickness of beam (m)
    double width = 1.0e-2;           // Width of beam (m)
    double area;            // Cross-section area of beam (m^2)
    double inertia;         // Moment of inertia of beam (m^4)
    int nelement;           // Number of element in a beam
    int ndof;               // Number of degree of freedoms of a beam
    int botCnstr;           // Bottom constraint, 1: roller, 2: fixed, 0: free
    int topCnstr;           // Top constraint, 1: roller, 2: fixed, 0: free
    VectorXd position;      // Position vector of beam (m)
    VectorXd velocity;      // Velocity vector of beam (m/s)
    VectorXd acceleration;  // Acceleration vector of beam (m/s^2)
    beam_forces * forces;     // All forces of beam
    friend class beam_builder;
public:
    beam() = default;
    ~beam() = default;
    void set_area();
    void set_inertia();
    void set_ndof();
    double get_E() {return E;}
    double get_rho() {return rho;}
    double get_length() {return length;}
    double get_thick() {return thick;}
    double get_width() {return width;}
    double get_area() {return area;}
    double get_inertia() {return inertia;}
    int get_nelement() {return nelement;}
    int get_ndof() {return ndof;}
    int get_botCnstr() {return botCnstr;}
    int get_topCnstr() {return topCnstr;}
    VectorXd get_position() {return position;}
    VectorXd get_velocity() {return velocity;}
    VectorXd get_acceleration() {return acceleration;}
    void set_gravity_force(VectorXd Qg) {forces->set_Q_gravity(Qg);};
    void set_elastic_force(VectorXd Qe) {forces->set_Q_elastic(Qe);};
    void set_dist_force(VectorXd Qd) {forces->set_Q_dist(Qd);};
    void set_point_force(VectorXd Qp) {forces->set_Q_point(Qp);};
    VectorXd get_gravity_force() {return forces->get_Q_gravity();};
    VectorXd get_elastic_force() {return forces->get_Q_elastic();};
    VectorXd get_dist_force() {return forces->get_Q_dist();};
    VectorXd get_point_force() {return forces->get_Q_dist();};
    friend ostream& operator<<(ostream&, const beam&);
};

class beam_builder {
private:
    beam* b;
public:
    beam_builder();
    ~beam_builder();
    void Reset();
    void set_E(double);
    void set_rho(double);
    void set_length(double);
    void set_thick(double);
    void set_width(double);
    void set_nelement(int);
    void set_botCnstr(int);
    void set_topCnstr(int);
    void set_position(VectorXd);
    void set_velocity();
    void set_velocity(VectorXd);
    void set_acceleration();
    void set_acceleration(VectorXd);
    beam* get_beam();
};


#endif //ANCF_MODEL_C___BEAM_H