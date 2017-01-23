#ifndef NOISY_H
#define NOISY_H
struct Noisy {
   Noisy() { cout << "Noisy()" << endl; }
   Noisy(const Noisy&) {
      cout << "Noisy(const Noisy&)" << endl;
   }
   Noisy(Noisy&&) { cout << "Noisy(Noisy&&)" << endl; }
   Noisy& operator=(const Noisy&) {
      cout << "operator=(const Noisy&)" << endl; return *this;
   }
   Noisy& operator=(Noisy&&) {
      cout << "operator=(Noisy&&)" << endl; return *this;
   }
   ~Noisy() { cout << "~Noisy()" << endl; }
};
#endif
