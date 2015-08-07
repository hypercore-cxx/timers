#include "index.h"

export {

  Timeout t;

  public:

    void sleep(int n) {
      t.sleep(n);
    }

    Timeout setTimeout(int n) {
      Timeout timeout;
      timeout.set(n);
      return timeout;
    }
}

