#ifndef PRECOND_VIOLATED_EXCEP_
#define PRECOND_VIOLATED_EXCEP_

#include <stdexcept>
#include <string>

/** @class PrecondViolatedExcep PrecondViolatedExcep.h "PrecondViolatedExcep.h"
 *
 *  Specification for an object thrown on violation of precondition. */
class PrecondViolatedExcep : public std::logic_error {
public:
   explicit PrecondViolatedExcep(const std::string& message = "");

   virtual ~PrecondViolatedExcep() noexcept = default;
};

#endif
