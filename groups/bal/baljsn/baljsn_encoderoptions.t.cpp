// baljsn_encoderoptions.t.cpp                                        -*-C++-*-

#include <baljsn_encoderoptions.h>

#include <bslim_testutil.h>

#include <bslma_default.h>
#include <bslma_defaultallocatorguard.h>
#include <bslma_testallocator.h>

#include <bsls_assert.h>
#include <bsls_asserttest.h>

#include <bsl_climits.h>
#include <bsl_cstdlib.h>
#include <bsl_iostream.h>
#include <bsl_sstream.h>

using namespace BloombergLP;
using namespace bsl;

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                 Overview
//                                 --------
// The component under test implements a single, simply constrained
// (value-semantic) attribute class.  The Primary Manipulators and Basic
// Accessors are therefore, respectively, the attribute setters and getters,
// each of which follows our standard unconstrained attribute-type naming
// conventions: 'setAttributeName' and 'attributeName'.
//
// Primary Manipulators:
//: o 'setInitialIndentLevel'
//: o 'setSpacesPerLevel'
//: o 'setEncodingStyle'
//: o 'setEncodeEmptyArrays'
//: o 'setEncodeNullElements'
//: o 'setDatetimeFractionalSecondPrecision'
//
// Basic Accessors:
//: o 'initialIndentLevel'
//: o 'spacesPerLevel'
//: o 'encodingStyle'
//: o 'encodeEmptyArrays'
//: o 'encodeNullElements'
//: o 'datetimeFractionalSecondPrecision'
//
// Certain standard value-semantic-type test cases are omitted:
//: o [ 8] -- 'swap' is not implemented for this class.
//: o [10] -- BSLX streaming is not (yet) implemented for this class.
//
// Global Concerns:
//: o ACCESSOR methods are declared 'const'.
//: o Precondition violations are detected in appropriate build modes.
//: o No memory is allocated from any allocator.
//
// Global Assumptions:
//: o ACCESSOR methods are 'const' thread-safe.
//: o Individual attribute types are presumed to be *alias-safe*; hence, only
//:   certain methods require the testing of this property:
//:   o copy-assignment
// ----------------------------------------------------------------------------
// CREATORS
// [ 2] baljsn::EncoderOptions();
// [ 7] baljsn::EncoderOptions(const baljsn::EncoderOptions& original);
// [ 2] ~baljsn::EncoderOptions();
//
// MANIPULATORS
// [ 9] operator=(const baljsn::EncoderOptions& rhs);
// [10] STREAM& bdexStreamIn(STREAM& stream, int version);
// [ 3] setInitialIndentLevel(int value);
// [ 3] setSpacesPerLevel(int value);
// [ 3] setEncodingStyle(EncodingStyle value);
// [ 3] setEncodeEmptyArrays(bool value);
// [ 3] setEncodeNullElements(bool value);
//
// ACCESSORS
// [10] STREAM& bdexStreamOut(STREAM& stream, int version) const;
// [ 4] int initialIndentLevel() const;
// [ 4] int spacesPerLevel() const;
// [ 4] int encodingStyle() const;
// [ 4] bool encodeEmptyArrays() const;
// [ 4] bool encodeNullElements() const;
//
// [ 5] ostream& print(ostream& s, int level = 0, int sPL = 4) const;
//
// FREE OPERATORS
// [ 6] bool operator==(const baljsn::EncoderOptions& lhs, rhs);
// [ 6] bool operator!=(const baljsn::EncoderOptions& lhs, rhs);
// [ 5] operator<<(ostream& s, const baljsn::EncoderOptions& d);
// ----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [11] USAGE EXAMPLE

// ============================================================================
//                     STANDARD BDE ASSERT TEST FUNCTION
// ----------------------------------------------------------------------------

namespace {

int testStatus = 0;

void aSsErT(bool condition, const char *message, int line)
{
    if (condition) {
        cout << "Error " __FILE__ "(" << line << "): " << message
             << "    (failed)" << endl;

        if (0 <= testStatus && testStatus <= 100) {
            ++testStatus;
        }
    }
}

}  // close unnamed namespace

// ============================================================================
//               STANDARD BDE TEST DRIVER MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT       BSLIM_TESTUTIL_ASSERT
#define ASSERTV      BSLIM_TESTUTIL_ASSERTV

#define LOOP_ASSERT  BSLIM_TESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BSLIM_TESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BSLIM_TESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BSLIM_TESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLIM_TESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLIM_TESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLIM_TESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLIM_TESTUTIL_LOOP6_ASSERT

#define Q            BSLIM_TESTUTIL_Q   // Quote identifier literally.
#define P            BSLIM_TESTUTIL_P   // Print identifier and value.
#define P_           BSLIM_TESTUTIL_P_  // P(X) without '\n'.
#define T_           BSLIM_TESTUTIL_T_  // Print a tab (w/o newline).
#define L_           BSLIM_TESTUTIL_L_  // current Line number

// ============================================================================
//                     NEGATIVE-TEST MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT_SAFE_PASS(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS(EXPR)
#define ASSERT_SAFE_FAIL(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL(EXPR)
#define ASSERT_PASS(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS(EXPR)
#define ASSERT_FAIL(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL(EXPR)
#define ASSERT_OPT_PASS(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS(EXPR)
#define ASSERT_OPT_FAIL(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL(EXPR)

#define ASSERT_SAFE_PASS_RAW(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS_RAW(EXPR)
#define ASSERT_SAFE_FAIL_RAW(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL_RAW(EXPR)
#define ASSERT_PASS_RAW(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS_RAW(EXPR)
#define ASSERT_FAIL_RAW(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL_RAW(EXPR)
#define ASSERT_OPT_PASS_RAW(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS_RAW(EXPR)
#define ASSERT_OPT_FAIL_RAW(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL_RAW(EXPR)

// ============================================================================
//                        GLOBAL TYPEDEFS FOR TESTING
// ----------------------------------------------------------------------------

typedef baljsn::EncoderOptions                Obj;
typedef baljsn::EncoderOptions::EncodingStyle Style;

// ============================================================================
//                                TYPE TRAITS
// ----------------------------------------------------------------------------

// ============================================================================
//                             GLOBAL TEST DATA
// ----------------------------------------------------------------------------

// Define DEFAULT DATA (potentially) used by test cases 3, 7, (8), 9, and (10)

struct DefaultDataRow {
    int   d_line;                // source line number
    int   d_initialIndentLevel;
    int   d_spacesPerLevel;
    Style d_encodingStyle;
    bool  d_encodeEmptyArrays;
    bool  d_encodeNullElements;
};

static
const DefaultDataRow DEFAULT_DATA[] =
{
    //LINE  INDENT   SPL       STYLE                 EEA    ENE
    //----  ------   ---       -----                 ---    ---

    // default (must be first)
    { L_,       0,       0,    Obj::e_COMPACT,  false, false  },

    // 'initialIndentLevel'
    { L_,       1,       0,    Obj::e_PRETTY,   false, false  },
    { L_, INT_MAX,       0,    Obj::e_COMPACT,  false, false  },

    // 'spacesPerLevel'
    { L_,       0,       1,    Obj::e_PRETTY,   false, false  },
    { L_,       0, INT_MAX,    Obj::e_COMPACT,  false, false  },

    // 'encodingStyle'
    { L_, INT_MAX,       1,    Obj::e_PRETTY,   false, false  },
    { L_,       1, INT_MAX,    Obj::e_COMPACT,  false, false  },

    // 'encodeEmptyArrays'
    { L_, INT_MAX,       1,    Obj::e_PRETTY,   true,  false  },
    { L_,       1, INT_MAX,    Obj::e_COMPACT,  true,  false  },

    // 'encodeNullElements'
    { L_, INT_MAX,       1,    Obj::e_PRETTY,   false, true   },
    { L_,       1, INT_MAX,    Obj::e_COMPACT,  false, true   },
};
const int DEFAULT_NUM_DATA = sizeof DEFAULT_DATA / sizeof *DEFAULT_DATA;

// ============================================================================
//                               MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int                 test = argc > 1 ? atoi(argv[1]) : 0;
    bool             verbose = argc > 2;
    bool         veryVerbose = argc > 3;
    bool     veryVeryVerbose = argc > 4;
    bool veryVeryVeryVerbose = argc > 5;

    bsl::cout << "TEST " << __FILE__ << " CASE " << test << bsl::endl;;

    bslma::TestAllocator globalAllocator("global", veryVeryVeryVerbose);
    bslma::Default::setGlobalAllocator(&globalAllocator);

    bslma::TestAllocator defaultAllocator("default", veryVeryVeryVerbose);
    bslma::Default::setDefaultAllocatorRaw(&defaultAllocator);

    switch (test) { case 0:  // Zero is always the leading case.
      case 11: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Extracted from component header file.
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "USAGE EXAMPLE" << endl
                          << "=============" << endl;

///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Creating and populating an options object
/// - - - - - - - - - - - - - - - - - - - - - - - - - -
// This component is designed to be used at a higher level to set the options
// for encoding objects in the JSON format.  This example shows how to create
// and populate an options object.
//
// First, we default-construct a 'baljsn::EncoderOptions' object:
//..
    const int  INITIAL_INDENT_LEVEL = 1;
    const int  SPACES_PER_LEVEL     = 4;
    const bool ENCODE_EMPTY_ARRAYS  = true;
    const bool ENCODE_NULL_ELEMENTS = true;

    baljsn::EncoderOptions options;
    ASSERT(0 == options.initialIndentLevel());
    ASSERT(0 == options.spacesPerLevel());
    ASSERT(baljsn::EncoderOptions::e_COMPACT == options.encodingStyle());
    ASSERT(false == options.encodeEmptyArrays());
    ASSERT(false == options.encodeNullElements());
//..
// Next, we populate that object to encode in a pretty format using a
// pre-defined initial indent level and spaces per level:
//..
    options.setEncodingStyle(baljsn::EncoderOptions::e_PRETTY);
    ASSERT(baljsn::EncoderOptions::e_PRETTY == options.encodingStyle());

    options.setInitialIndentLevel(INITIAL_INDENT_LEVEL);
    ASSERT(INITIAL_INDENT_LEVEL == options.initialIndentLevel());

    options.setSpacesPerLevel(SPACES_PER_LEVEL);
    ASSERT(SPACES_PER_LEVEL == options.spacesPerLevel());

    options.setEncodeEmptyArrays(ENCODE_EMPTY_ARRAYS);
    ASSERT(ENCODE_EMPTY_ARRAYS == options.encodeEmptyArrays());

    options.setEncodeNullElements(ENCODE_NULL_ELEMENTS);
    ASSERT(ENCODE_NULL_ELEMENTS == options.encodeNullElements());
//..
      } break;
      case 10: {
        // --------------------------------------------------------------------
        // TESTING BDEX STREAMING
        //
        // Concerns:
        //   N/A
        //
        // Plan:
        //   N/A
        //
        // Testing:
        //  Reserved for 'swap' testing.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING BDEX STREAMING" << endl
                          << "======================" << endl;
      } break;
      case 9: {
        // --------------------------------------------------------------------
        // TESTING COPY-ASSIGNMENT OPERATOR
        //   Ensure that we can assign the value of any object of the class to
        //   any object of the class, such that the two objects subsequently
        //   have the same value.
        //
        // Concerns:
        //: 1 The assignment operator can change the value of any modifiable
        //:   target object to that of any source object.
        //:
        //: 2 The signature and return type are standard.
        //:
        //: 3 The reference returned is to the target object (i.e., '*this').
        //:
        //: 4 The value of the source object is not modified.
        //:
        //: 5 Assigning an object to itself behaves as expected (alias-safety).
        //
        // Plan:
        //: 1 Use the address of 'operator=' to initialize a member-function
        //:   pointer having the appropriate signature and return type for the
        //:   copy-assignment operator defined in this component.  (C-2)
        //:
        //: 2 Using the table-driven technique, specify a set of (unique) valid
        //:   object values (one per row) in terms of their individual
        //:   attributes, including (a) first, the default value, and (b)
        //:   boundary values corresponding to every range of values that each
        //:   individual attribute can independently attain.
        //:
        //: 3 For each row 'R1' (representing a distinct object value, 'V') in
        //:   the table described in P-3:  (C-1, 3..4)
        //:
        //:   1 Create two 'const' 'Obj', 'Z' and 'ZZ', each having the value
        //:     'V'.
        //:
        //:   2 Execute an inner loop that iterates over each row 'R2'
        //:     (representing a distinct object value, 'W') in the table
        //:     described in P-3:
        //:
        //:   3 For each of the iterations (P-3.2):  (C-1, 3..4)
        //:
        //:     1 Use the value constructor to create a modifiable 'Obj', 'mX',
        //:       having the value 'W'.
        //:
        //:     2 Assign 'mX' from 'Z'.
        //:
        //:     3 Verify that the address of the return value is the same as
        //:       that of 'mX'.  (C-3)
        //:
        //:     4 Use the equality-comparison operator to verify that: (C-1, 4)
        //:
        //:       1 The target object, 'mX', now has the same value as that of
        //:         'Z'.  (C-1)
        //:
        //:       2 'Z' still has the same value as that of 'ZZ'.  (C-4)
        //:
        //: 4 Repeat steps similar to those described in P-2 except that, this
        //:   time, the source object, 'Z', is a reference to the target
        //:   object, 'mX', and both 'mX' and 'ZZ' are initialized to have the
        //:   value 'V'.  For each row (representing a distinct object value,
        //:   'V') in the table described in P-2:  (C-5)
        //:
        //:   1 Use the value constructor to create a modifiable 'Obj' 'mX';
        //:     also use the value constructor to create a 'const' 'Obj' 'ZZ'.
        //:
        //:   2 Let 'Z' be a reference providing only 'const' access to 'mX'.
        //:
        //:   3 Assign 'mX' from 'Z'.
        //:
        //:   4 Verify that the address of the return value is the same as that
        //:     of 'mX'.  (C-3)
        //:
        //:   5 Use the equality-comparison operator to verify that the
        //:     target object, 'Z', still has the same value as that of 'ZZ'.
        //:     (C-5)
        //
        // Testing:
        //   operator=(const baljsn::EncoderOptions& rhs);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING COPY-ASSIGNMENT OPERATOR" << endl
                          << "================================" << endl;

        if (verbose) cout <<
                 "\nAssign the address of the operator to a variable." << endl;
        {
            typedef Obj& (Obj::*operatorPtr)(const Obj&);

            // Verify that the signature and return type are standard.

            operatorPtr operatorAssignment = &Obj::operator=;

            (void)operatorAssignment;  // quash potential compiler warning
        }

        if (verbose) cout << "\nUse table of distinct object values." << endl;

        const int NUM_DATA                     = DEFAULT_NUM_DATA;
        const DefaultDataRow (&DATA)[NUM_DATA] = DEFAULT_DATA;

        if (verbose) cout <<
                         "\nCopy-assign every value into every value." << endl;

        for (int ti = 0; ti < NUM_DATA; ++ti) {
            const int   LINE1    = DATA[ti].d_line;
            const int   INDENT1  = DATA[ti].d_initialIndentLevel;
            const int   SPL1     = DATA[ti].d_spacesPerLevel;
            const Style STYLE1   = DATA[ti].d_encodingStyle;
            const bool  EEA1     = DATA[ti].d_encodeEmptyArrays;
            const bool  ENE1     = DATA[ti].d_encodeNullElements;

            Obj mZ;  const Obj& Z = mZ;
            mZ.setInitialIndentLevel(INDENT1);
            mZ.setSpacesPerLevel(SPL1);
            mZ.setEncodingStyle(STYLE1);
            mZ.setEncodeEmptyArrays(EEA1);
            mZ.setEncodeNullElements(ENE1);

            Obj mZZ;  const Obj& ZZ = mZZ;
            mZZ.setInitialIndentLevel(INDENT1);
            mZZ.setSpacesPerLevel(SPL1);
            mZZ.setEncodingStyle(STYLE1);
            mZZ.setEncodeEmptyArrays(EEA1);
            mZZ.setEncodeNullElements(ENE1);

            if (veryVerbose) { T_ P_(LINE1) P_(Z) P(ZZ) }

            // Ensure the first row of the table contains the
            // default-constructed value.

            static bool firstFlag = true;
            if (firstFlag) {
                LOOP3_ASSERT(LINE1, Obj(), Z, Obj() == Z);
                firstFlag = false;
            }

            for (int tj = 0; tj < NUM_DATA; ++tj) {
                const int   LINE2    = DATA[tj].d_line;
                const int   INDENT2  = DATA[tj].d_initialIndentLevel;
                const int   SPL2     = DATA[tj].d_spacesPerLevel;
                const Style STYLE2   = DATA[tj].d_encodingStyle;
                const bool  EEA2     = DATA[tj].d_encodeEmptyArrays;
                const bool  ENE2     = DATA[tj].d_encodeNullElements;

                Obj mX;  const Obj& X = mX;
                mX.setInitialIndentLevel(INDENT2);
                mX.setSpacesPerLevel(SPL2);
                mX.setEncodingStyle(STYLE2);
                mX.setEncodeEmptyArrays(EEA2);
                mX.setEncodeNullElements(ENE2);

                if (veryVerbose) { T_ P_(LINE2) P(X) }

                LOOP4_ASSERT(LINE1, LINE2, Z, X, (Z == X) == (LINE1 == LINE2));

                Obj *mR = &(mX = Z);
                LOOP4_ASSERT(LINE1, LINE2,  Z,   X,  Z == X);
                LOOP4_ASSERT(LINE1, LINE2, mR, &mX, mR == &mX);

                LOOP4_ASSERT(LINE1, LINE2, ZZ, Z, ZZ == Z);
            }

            if (verbose) cout << "Testing self-assignment" << endl;

            {
                Obj mX;  const Obj& X = mX;
                mX.setInitialIndentLevel(INDENT1);
                mX.setSpacesPerLevel(SPL1);
                mX.setEncodingStyle(STYLE1);
                mX.setEncodeEmptyArrays(EEA1);
                mX.setEncodeNullElements(ENE1);

                Obj mZZ;  const Obj& ZZ = mZZ;
                mZZ.setInitialIndentLevel(INDENT1);
                mZZ.setSpacesPerLevel(SPL1);
                mZZ.setEncodingStyle(STYLE1);
                mZZ.setEncodeEmptyArrays(EEA1);
                mZZ.setEncodeNullElements(ENE1);

                const Obj& Z = mX;

                LOOP3_ASSERT(LINE1, ZZ, Z, ZZ == Z);

                Obj *mR = &(mX = Z);
                LOOP3_ASSERT(LINE1, ZZ,   Z, ZZ == Z);
                LOOP3_ASSERT(LINE1, mR, &mX, mR == &mX);
            }
        }
      } break;
      case 8: {
        // --------------------------------------------------------------------
        // TESTING SWAP MEMBER AND FREE FUNCTIONS
        //
        // Concerns:
        //   N/A
        //
        // Plan:
        //   N/A
        //
        // Testing:
        //  Reserved for 'swap' testing.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING SWAP MEMBER AND FREE FUNCTIONS" << endl
                          << "======================================" << endl;
      } break;
      case 7: {
        // --------------------------------------------------------------------
        // TESTING COPY CONSTRUCTOR
        //   Ensure that we can create a distinct object of the class from any
        //   other one, such that the two objects have the same value.
        //
        // Concerns:
        //: 1 The copy constructor creates an object having the same value as
        //:   that of the supplied original object.
        //:
        //: 2 The original object is passed as a reference providing
        //:   non-modifiable access to that object.
        //:
        //: 3 The value of the original object is unchanged.
        //
        // Plan:
        //: 1 Using the table-driven technique, specify a set of (unique) valid
        //:   object values (one per row) in terms of their individual
        //:   attributes, including (a) first, the default value, and (b)
        //:   boundary values corresponding to every range of values that each
        //:   individual attribute can independently attain.
        //:
        //: 2 For each row (representing a distinct object value, 'V') in the
        //:   table described in P-1:  (C-1..3)
        //:
        //:   1 Use the value constructor to create two 'const' 'Obj', 'Z' and
        //:     'ZZ', each having the value 'V'.
        //:
        //:   2 Use the copy constructor to create an object 'X',
        //:     supplying it the 'const' object 'Z'.  (C-2)
        //:
        //:   3 Use the equality-comparison operator to verify that:
        //:     (C-1, 3)
        //:
        //:     1 The newly constructed object, 'X', has the same value as 'Z'.
        //:       (C-1)
        //:
        //:     2 'Z' still has the same value as 'ZZ'.  (C-3)
        //
        // Testing:
        //   baljsn::EncoderOptions(const baljsn::EncoderOptions& o);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING COPY CONSTRUCTOR" << endl
                          << "========================" << endl;

        if (verbose) cout << "\nUse table of distinct object values." << endl;

        const int NUM_DATA                     = DEFAULT_NUM_DATA;
        const DefaultDataRow (&DATA)[NUM_DATA] = DEFAULT_DATA;

        if (verbose) cout <<
                        "\nCopy construct an object from every value." << endl;

        for (int ti = 0; ti < NUM_DATA; ++ti) {
            const int   LINE    = DATA[ti].d_line;
            const int   INDENT  = DATA[ti].d_initialIndentLevel;
            const int   SPL     = DATA[ti].d_spacesPerLevel;
            const Style STYLE   = DATA[ti].d_encodingStyle;
            const bool  EEA     = DATA[ti].d_encodeEmptyArrays;
            const bool  ENE     = DATA[ti].d_encodeNullElements;

            Obj mZ;  const Obj& Z = mZ;
            mZ.setInitialIndentLevel(INDENT);
            mZ.setSpacesPerLevel(SPL);
            mZ.setEncodingStyle(STYLE);
            mZ.setEncodeEmptyArrays(EEA);
            mZ.setEncodeNullElements(ENE);

            Obj mZZ;  const Obj& ZZ = mZZ;
            mZZ.setInitialIndentLevel(INDENT);
            mZZ.setSpacesPerLevel(SPL);
            mZZ.setEncodingStyle(STYLE);
            mZZ.setEncodeEmptyArrays(EEA);
            mZZ.setEncodeNullElements(ENE);

            if (veryVerbose) { T_ P_(Z) P(ZZ) }

            Obj mX(Z);  const Obj& X = mX;

            if (veryVerbose) { T_ T_ P(X) }

            // Ensure the first row of the table contains the
            // default-constructed value.

            static bool firstFlag = true;
            if (firstFlag) {
                LOOP3_ASSERT(LINE, Obj(), Z, Obj() == Z)
                firstFlag = false;
            }

            // Verify the value of the object.

            LOOP3_ASSERT(LINE,  Z, X,  Z == X);

            // Verify that the value of 'Z' has not changed.

            LOOP3_ASSERT(LINE, ZZ, Z, ZZ == Z);
        }  // end foreach row

      } break;
      case 6: {
        // --------------------------------------------------------------------
        // TESTING EQUALITY-COMPARISON OPERATORS
        //   Ensure that '==' and '!=' are the operational definition of value.
        //
        // Concerns:
        //: 1 Two objects, 'X' and 'Y', compare equal if and only if each of
        //:   their corresponding salient attributes respectively compares
        //:   equal.
        //:
        //: 2 All salient attributes participate in the comparison.
        //:
        //: 3 No non-salient attributes (i.e., 'allocator') participate.
        //:
        //: 4 'true  == (X == X)'  (i.e., identity)
        //:
        //: 5 'false == (X != X)'  (i.e., identity)
        //:
        //: 6 'X == Y' if and only if 'Y == X'  (i.e., commutativity)
        //:
        //: 7 'X != Y' if and only if 'Y != X'  (i.e., commutativity)
        //:
        //: 8 'X != Y' if and only if '!(X == Y)'
        //:
        //: 9 Comparison is symmetric with respect to user-defined conversion
        //:   (i.e., both comparison operators are free functions).
        //:
        //:10 Non-modifiable objects can be compared (i.e., objects or
        //:   references providing only non-modifiable access).
        //:
        //:11 The equality operator's signature and return type are standard.
        //:
        //:12 The inequality operator's signature and return type are standard.
        //
        // Plan:
        //: 1 Use the respective addresses of 'operator==' and 'operator!=' to
        //:   initialize function pointers having the appropriate signatures
        //:   and return types for the two homogeneous, free equality-
        //:   comparison operators defined in this component.
        //:   (C-9..12)
        //:
        //: 2 Using the table-driven technique, specify a set of distinct
        //:   object values (one per row) in terms of their individual salient
        //:   attributes such that for each salient attribute, there exists a
        //:   pair of rows that differ (slightly) in only the column
        //:   corresponding to that attribute.
        //:
        //: 3 For each row 'R1' in the table of P-3:  (C-1..8)
        //:
        //:   1 Create a single object, and use it to verify the reflexive
        //:     (anti-reflexive) property of equality (inequality) in the
        //:     presence of aliasing.  (C-4..5)
        //:
        //:   2 For each row 'R2' in the table of P-3:  (C-1..3, 6..8)
        //:
        //:     1 Record, in 'EXP', whether or not distinct objects created
        //:       from 'R1' and 'R2', respectively, are expected to have the
        //:       same value.
        //:
        //:     2 Create an object 'X' having the value 'R1'.
        //:
        //:     3 Create an object 'Y' having the value 'R2'.
        //:
        //:     4 Verify the commutative property and expected return value for
        //:       both '==' and '!='.  (C-1..3, 6..8)
        //
        // Testing:
        //   bool operator==(const baljsn::EncoderOptions& lhs, rhs);
        //   bool operator!=(const baljsn::EncoderOptions& lhs, rhs);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING EQUALITY-COMPARISON OPERATORS" << endl
                          << "=====================================" << endl;

        if (verbose) cout <<
                "\nAssign the address of each operator to a variable." << endl;
        {
            using namespace baljsn;
            typedef bool (*operatorPtr)(const Obj&, const Obj&);

            // Verify that the signatures and return types are standard.

            operatorPtr operatorEq = operator==;
            operatorPtr operatorNe = operator!=;

            (void)operatorEq;  // quash potential compiler warnings
            (void)operatorNe;
        }

        if (verbose) cout <<
            "\nDefine appropriate individual attribute values, 'Ai' and 'Bi'."
                                                                       << endl;
        // ---------------
        // Attribute Types
        // ---------------

        typedef int   T1;        // 'initialIndentLevel'
        typedef int   T2;        // 'spacesPerLevel'
        typedef Style T3;        // 'encodingStyle'
        typedef bool  T4;        // 'encodeEmptyArrays'
        typedef bool  T5;        // 'encodeNullElements'

                 // ----------------------------------------
                 // Attribute 1 Values: 'initialIndentLevel'
                 // ----------------------------------------

        const T1 A1 = 1;               // baseline
        const T1 B1 = INT_MAX;

                   // ------------------------------------
                   // Attribute 2 Values: 'spacesPerLevel'
                   // ------------------------------------

        const T2 A2 = INT_MAX;         // baseline
        const T2 B2 = 10;

                   // -----------------------------------
                   // Attribute 3 Values: 'encodingStyle'
                   // -----------------------------------

        const T3 A3 = Obj::e_COMPACT;         // baseline
        const T3 B3 = Obj::e_PRETTY;

                 // ---------------------------------------
                 // Attribute 4 Values: 'encodeEmptyArrays'
                 // ---------------------------------------

        const T4 A4 = false;           // baseline
        const T4 B4 = true;

                 // ----------------------------------------
                 // Attribute 5 Values: 'encodeNullElements'
                 // ----------------------------------------

        const T5 A5 = false;           // baseline
        const T5 B5 = true;

        if (verbose) cout <<
            "\nCreate a table of distinct, but similar object values." << endl;

        static const struct {
            int   d_line;        // source line number
            int   d_initialIndentLevel;
            int   d_spacesPerLevel;
            Style d_encodingStyle;
            bool  d_encodeEmptyArrays;
            bool  d_encodeNullElements;
        } DATA[] = {

        // The first row of the table below represents an object value
        // consisting of "baseline" attribute values (A1..An).  Each subsequent
        // row differs (slightly) from the first in exactly one attribute value
        // (Bi).

        //LINE  INDENT  SPL  STYLE   EEA  ENE
        //----  ------  ---  -----   ---  ---

        { L_,       A1,   A2,   A3,  A4,   A5  },          // baseline

        { L_,       B1,   A2,   A3,  A4,   A5  },
        { L_,       A1,   B2,   A3,  A4,   A5  },
        { L_,       A1,   A2,   B3,  A4,   A5  },
        { L_,       A1,   A2,   A3,  B4,   A5  },
        { L_,       A1,   A2,   A3,  A4,   B5  },

        };
        const int NUM_DATA = sizeof DATA / sizeof *DATA;

        if (verbose) cout << "\nCompare every value with every value." << endl;

        for (int ti = 0; ti < NUM_DATA; ++ti) {
            const int   LINE1    = DATA[ti].d_line;
            const int   INDENT1  = DATA[ti].d_initialIndentLevel;
            const int   SPL1     = DATA[ti].d_spacesPerLevel;
            const Style STYLE1   = DATA[ti].d_encodingStyle;
            const bool  EEA1     = DATA[ti].d_encodeEmptyArrays;
            const bool  ENE1     = DATA[ti].d_encodeNullElements;

            if (veryVerbose) { T_ P_(LINE1) P_(INDENT1)
                                  P_(SPL1)  P_(STYLE1) P_(EEA1) P_(ENE1) }

            // Ensure an object compares correctly with itself (alias test).
            {
                Obj mX;  const Obj& X = mX;

                mX.setInitialIndentLevel(INDENT1);
                mX.setSpacesPerLevel(SPL1);
                mX.setEncodingStyle(STYLE1);
                mX.setEncodeEmptyArrays(EEA1);
                mX.setEncodeNullElements(ENE1);

                LOOP2_ASSERT(LINE1, X,   X == X);
                LOOP2_ASSERT(LINE1, X, !(X != X));
            }

            for (int tj = 0; tj < NUM_DATA; ++tj) {
                const int   LINE2    = DATA[tj].d_line;
                const int   INDENT2  = DATA[tj].d_initialIndentLevel;
                const int   SPL2     = DATA[tj].d_spacesPerLevel;
                const Style STYLE2   = DATA[tj].d_encodingStyle;
                const bool  EEA2     = DATA[tj].d_encodeEmptyArrays;
                const bool  ENE2     = DATA[tj].d_encodeNullElements;

                if (veryVerbose) { T_ P_(LINE1) P_(INDENT2)
                                      P_(SPL2) P_(STYLE2) P_(EEA2) P_(ENE2) }

                const bool EXP = ti == tj;  // expected for equality comparison

                Obj mX;  const Obj& X = mX;
                Obj mY;  const Obj& Y = mY;

                mX.setInitialIndentLevel(INDENT1);
                mX.setSpacesPerLevel(SPL1);
                mX.setEncodingStyle(STYLE1);
                mX.setEncodeEmptyArrays(EEA1);
                mX.setEncodeNullElements(ENE1);

                mY.setInitialIndentLevel(INDENT2);
                mY.setSpacesPerLevel(SPL2);
                mY.setEncodingStyle(STYLE2);
                mY.setEncodeEmptyArrays(EEA2);
                mY.setEncodeNullElements(ENE2);

                if (veryVerbose) { T_ T_ T_ P_(EXP) P_(X) P(Y) }

                // Verify value, and commutative.

                LOOP4_ASSERT(LINE1, LINE2, X, Y,  EXP == (X == Y));
                LOOP4_ASSERT(LINE1, LINE2, Y, X,  EXP == (Y == X));

                LOOP4_ASSERT(LINE1, LINE2, X, Y, !EXP == (X != Y));
                LOOP4_ASSERT(LINE1, LINE2, Y, X, !EXP == (Y != X));
            }
        }
      } break;
      case 5: {
        // --------------------------------------------------------------------
        // TESTING PRINT AND OUTPUT OPERATOR
        //   Ensure that the value of the object can be formatted appropriately
        //   on an 'ostream' in some standard, human-readable form.
        //
        // Concerns:
        //: 1 The 'print' method writes the value to the specified 'ostream'.
        //:
        //: 2 The 'print' method writes the value in the intended format.
        //:
        //: 3 The output using 's << obj' is the same as 'obj.print(s, 0, -1)',
        //:   but with each "attributeName = " elided.
        //:
        //: 4 The 'print' method signature and return type are standard.
        //:
        //: 5 The 'print' method returns the supplied 'ostream'.
        //:
        //: 6 The output 'operator<<' signature and return type are standard.
        //:
        //: 7 The output 'operator<<' returns the supplied 'ostream'.
        //
        // Plan:
        //: 1 Use the addresses of the 'print' member function and 'operator<<'
        //:   free function defined in this component to initialize,
        //:   respectively, member-function and free-function pointers having
        //:   the appropriate signatures and return types.  (C-4, 6)
        //:
        //: 2 Using the table-driven technique, define twelve carefully
        //:   selected combinations of (two) object values ('A' and 'B'),
        //:   having distinct values for each corresponding salient attribute,
        //:   and various values for the two formatting parameters, along with
        //:   the expected output
        //:     ( 'value' x  'level'   x 'spacesPerLevel' ):
        //:     1 { A   } x {  0     } x {  0, 1, -1 }  -->  3 expected outputs
        //:     2 { A   } x {  3, -3 } x {  0, 2, -2 }  -->  6 expected outputs
        //:     3 { B   } x {  2     } x {  3        }  -->  1 expected output
        //:     4 { A B } x { -9     } x { -9        }  -->  2 expected output
        //:
        //: 3 For each row in the table defined in P-2.1:  (C-1..3, 5, 7)
        //:
        //:   1 Using a 'const' 'Obj', supply each object value and pair of
        //:     formatting parameters to 'print', unless the parameters are,
        //:     arbitrarily, (-9, -9), in which case 'operator<<' will be
        //:     invoked instead.
        //:
        //:   2 Use a standard 'ostringstream' to capture the actual output.
        //:
        //:   3 Verify the address of what is returned is that of the
        //:     supplied stream.  (C-5, 7)
        //:
        //:   4 Compare the contents captured in P-2.2.2 with what is
        //:     expected.  (C-1..3)
        //
        // Testing:
        //   ostream& print(ostream& s, int level = 0, int sPL = 4) const;
        //   operator<<(ostream& s, const baljsn::EncoderOptions& d);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING PRINT AND OUTPUT OPERATOR" << endl
                          << "=================================" << endl;

        bslma::TestAllocator         da("default", veryVeryVeryVerbose);
        bslma::DefaultAllocatorGuard dag(&da);

        if (verbose) cout << "\nAssign the addresses of 'print' and "
                             "the output 'operator<<' to variables." << endl;
        {
            using namespace baljsn;
            typedef ostream& (Obj::*funcPtr)(ostream&, int, int) const;
            typedef ostream& (*operatorPtr)(ostream&, const Obj&);

            // Verify that the signatures and return types are standard.

            funcPtr     printMember = &Obj::print;
            operatorPtr operatorOp  = operator<<;

            (void)printMember;  // quash potential compiler warnings
            (void)operatorOp;
        }

        if (verbose) cout <<
             "\nCreate a table of distinct value/format combinations." << endl;

        Style C = Obj::e_COMPACT;
        Style P = Obj::e_PRETTY;

        const bool T = true;
        const bool F = false;

        static const struct {
            int         d_line;           // source line number
            int         d_level;
            int         d_spl;

            int         d_initialIndentLevel;
            int         d_spacesPerLevel;
            Style       d_encodingStyle;
            bool        d_encodeEmptyArrays;
            bool        d_encodeNullElements;

            const char *d_expected_p;
        } DATA[] = {

#define NL "\n"
#define SP " "

   // ------------------------------------------------------------------
   // P-2.1.1: { A } x { 0 } x { 0, 1, -1 } --> 3 expected outputs
   // ------------------------------------------------------------------

//LINE  L  SPL  IND  SPL STYLE EEA ENE EXP
//----  -  ---  ---  --- ----- --- --- ---

 { L_,  0,  0,  89,  10,    C,  T,  T,
   "["                                      NL
   "initialIndentLevel = 89"                NL
   "spacesPerLevel = 10"                    NL
   "encodingStyle = 0"                      NL
   "encodeEmptyArrays = true"               NL
   "encodeNullElements = true"              NL
   "datetimeFractionalSecondPrecision = 3"  NL
   "]"                                      NL
                                                                             },

 { L_,  0,  1,  89,  10,    P,  T,  T,
   "["                                       NL
   " initialIndentLevel = 89"                NL
   " spacesPerLevel = 10"                    NL
   " encodingStyle = 1"                      NL
   " encodeEmptyArrays = true"               NL
   " encodeNullElements = true"              NL
   " datetimeFractionalSecondPrecision = 3"  NL
   "]"                                       NL
                                                                             },

 { L_,  0, -1,  89,  10,    C,  T,  F,
   "["                                      SP
   "initialIndentLevel = 89"                SP
   "spacesPerLevel = 10"                    SP
   "encodingStyle = 0"                      SP
   "encodeEmptyArrays = true"               SP
   "encodeNullElements = false"             SP
   "datetimeFractionalSecondPrecision = 3"  SP
   "]"
                                                                             },

   // ------------------------------------------------------------------
   // P-2.1.2: { A } x { 3, -3 } x { 0, 2, -2 } --> 6 expected outputs
   // ------------------------------------------------------------------

//LINE  L  SPL  IND  SPL STYLE EEA ENE EXP
//----  -  ---  ---  --- ----- --- --- ---

 { L_,  3,  0,  89,  10,    C,  T,  T,
   "["                                      NL
   "initialIndentLevel = 89"                NL
   "spacesPerLevel = 10"                    NL
   "encodingStyle = 0"                      NL
   "encodeEmptyArrays = true"               NL
   "encodeNullElements = true"              NL
   "datetimeFractionalSecondPrecision = 3"  NL
   "]"                                      NL
                                                                             },

 { L_,  3,  2,  89,  10,    P,  F,  F,
   "      ["                                        NL
   "        initialIndentLevel = 89"                NL
   "        spacesPerLevel = 10"                    NL
   "        encodingStyle = 1"                      NL
   "        encodeEmptyArrays = false"              NL
   "        encodeNullElements = false"             NL
   "        datetimeFractionalSecondPrecision = 3"  NL
   "      ]"                                        NL
 },

 { L_,  3, -2,  89,  10,    C,  T,  F,
   "      ["                                SP
   "initialIndentLevel = 89"                SP
   "spacesPerLevel = 10"                    SP
   "encodingStyle = 0"                      SP
   "encodeEmptyArrays = true"               SP
   "encodeNullElements = false"             SP
   "datetimeFractionalSecondPrecision = 3"  SP
   "]"
                                                                             },

 { L_, -3,  0,  89,  10,    P,  F,  T,
   "["                                      NL
   "initialIndentLevel = 89"                NL
   "spacesPerLevel = 10"                    NL
   "encodingStyle = 1"                      NL
   "encodeEmptyArrays = false"              NL
   "encodeNullElements = true"              NL
   "datetimeFractionalSecondPrecision = 3"  NL
   "]"                                      NL
                                                                             },

 { L_, -3,  2,  89,  10,    P,  T,  F,
   "["                                              NL
   "        initialIndentLevel = 89"                NL
   "        spacesPerLevel = 10"                    NL
   "        encodingStyle = 1"                      NL
   "        encodeEmptyArrays = true"               NL
   "        encodeNullElements = false"             NL
   "        datetimeFractionalSecondPrecision = 3"  NL
   "      ]"                                        NL
                                                                             },

 { L_, -3, -2,  89,  10,    C,  T,  T,
   "["                                      SP
   "initialIndentLevel = 89"                SP
   "spacesPerLevel = 10"                    SP
   "encodingStyle = 0"                      SP
   "encodeEmptyArrays = true"               SP
   "encodeNullElements = true"              SP
   "datetimeFractionalSecondPrecision = 3"  SP
   "]"
                                                                             },

           // ----------------------------------------------------
           // P-2.1.3: { B } x { 2 } x { 3 } --> 1 expected output
           // ----------------------------------------------------

//LINE  L  SPL  IND  SPL STYLE EEA ENE EXP
//----  -  ---  ---  --- ----- --- --- ---

 { L_,  2,  3,  89,  10,    P,  T,  T,
   "      ["                                         NL
   "         initialIndentLevel = 89"                NL
   "         spacesPerLevel = 10"                    NL
   "         encodingStyle = 1"                      NL
   "         encodeEmptyArrays = true"               NL
   "         encodeNullElements = true"              NL
   "         datetimeFractionalSecondPrecision = 3"  NL
   "      ]"                                         NL
                                                                             },

        // -----------------------------------------------------------------
        // P-2.1.4: { A B } x { -9 } x { -9 } --> 2 expected outputs
        // -----------------------------------------------------------------

//LINE  L  SPL  IND  SPL STYLE EEA  ENE EXP
//----  -  ---  ---  --- ----- ---  --- ---

 { L_, -9, -9,  89,  10,    C,  F,  T, "[ 89 10 0 false true 3 ]"           },
 { L_, -9, -9,   7,   5,    P,  F,  F, "[ 7 5 1 false false 3 ]"            },

#undef NL
#undef SP

        };
        const int NUM_DATA = sizeof DATA / sizeof *DATA;

        if (verbose) cout << "\nTesting with various print specifications."
                          << endl;
        {
            for (int ti = 0; ti < NUM_DATA; ++ti) {
                const int         LINE   = DATA[ti].d_line;
                const int         L      = DATA[ti].d_level;
                const int         S      = DATA[ti].d_spl;

                const int         INDENT = DATA[ti].d_initialIndentLevel;
                const int         SPL    = DATA[ti].d_spacesPerLevel;
                const Style       STYLE  = DATA[ti].d_encodingStyle;
                const bool        EEA    = DATA[ti].d_encodeEmptyArrays;
                const bool        ENE    = DATA[ti].d_encodeNullElements;

                const char *const EXP    = DATA[ti].d_expected_p;

                if (veryVerbose) { T_ P_(L) P_(INDENT) P_(SPL)
                                      P_(STYLE) P_(EEA) P_(ENE) }

                if (veryVeryVerbose) { T_ T_ Q(EXPECTED) cout << EXP; }

                Obj mX;  const Obj& X = mX;
                mX.setInitialIndentLevel(INDENT);
                mX.setSpacesPerLevel(SPL);
                mX.setEncodingStyle(STYLE);
                mX.setEncodeEmptyArrays(EEA);
                mX.setEncodeNullElements(ENE);

                ostringstream os;

                if (-9 == L && -9 == S) {

                    // Verify supplied stream is returned by reference.

                    LOOP_ASSERT(LINE, &os == &(os << X));

                    if (veryVeryVerbose) { T_ T_ Q(operator<<) }
                }
                else {

                    // Verify supplied stream is returned by reference.

                    LOOP_ASSERT(LINE, &os == &X.print(os, L, S));

                    if (veryVeryVerbose) { T_ T_ Q(print) }
                }

                // Verify output is formatted as expected.

                if (veryVeryVerbose) { P(os.str()) }

                LOOP3_ASSERT(LINE, EXP, os.str(), EXP == os.str());
            }
        }
      } break;
      case 4: {
        // --------------------------------------------------------------------
        // TESTING ACCESSORS
        //
        // Concerns:
        //: 1 Each accessor returns the value of the corresponding attribute
        //:   of the object.
        //:
        //: 2 Each accessor method is declared 'const'.
        //
        // Plan:
        //   Here we use the default constructor and primary manipulators,
        //   which were fully tested in case 2, to further corroborate that
        //   these accessors are properly interpreting object state.
        //
        //: 1 Use the default constructor to create an object (having default
        //:   attribute values).
        //:
        //: 2 Verify that each basic accessor, invoked on a reference providing
        //:   non-modifiable access to the object created in P2, returns the
        //:   expected value.  (C-2)
        //:
        //: 3 For each salient attribute (contributing to value):  (C-1)
        //:   1 Use the corresponding primary manipulator to set the attribute
        //:     to a unique value.
        //:
        //:   2 Use the corresponding basic accessor to verify the new
        //:     expected value.  (C-1)
        //
        // Testing:
        //   int   initialIndentLevel() const;
        //   int   spacesPerLevel() const;
        //   Style encodingStyle() const;
        //   bool  encodeEmptyArrays() const;
        //   bool  encodeNullElements() const;
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING ACCESSORS" << endl
                          << "=================" << endl;

        // Attribute Types

        typedef int   T1;        // 'initialIndentLevel'
        typedef int   T2;        // 'spacesPerLevel'
        typedef Style T3;        // 'encodingStyle'
        typedef bool  T4;        // 'encodeEmptyArrays'
        typedef bool  T5;        // 'encodeNullElements'

        if (verbose) cout << "\nEstablish suitable attribute values." << endl;

          // -----------------------------------------------------
          // 'D' values: These are the default-constructed values.
          // -----------------------------------------------------

        const int   D1   = 0;                    // 'initialIndentLevel'
        const int   D2   = 0;                    // 'spacesPerLevel'
        const Style D3   = Obj::e_COMPACT;  // 'encodingStyle'
        const bool  D4   = false;                // 'encodeEmptyArrays'
        const bool  D5   = false;                // 'encodeNullElements'

                       // ----------------------------
                       // 'A' values: Boundary values.
                       // ----------------------------

        const int   A1   = INT_MAX;              // 'initialIndentLevel'
        const int   A2   = 4;                    // 'spacesPerLevel'
        const Style A3   = Obj::e_PRETTY;   // 'encodingStyle'
        const bool  A4   = true;                 // 'encodeEmptyArrays'
        const bool  A5   = true;                 // 'encodeNullElements'

        if (verbose) cout << "\nCreate an object." << endl;

        Obj mX;  const Obj& X = mX;

        if (verbose) cout <<
                "\nVerify all basic accessors report expected values." << endl;
        {
            const T1& initialIndentLevel = X.initialIndentLevel();
            LOOP2_ASSERT(D1, initialIndentLevel, D1 == initialIndentLevel);

            const T2& spacesPerLevel = X.spacesPerLevel();
            LOOP2_ASSERT(D2, spacesPerLevel, D2 == spacesPerLevel);

            const T3& encodingStyle = X.encodingStyle();
            LOOP2_ASSERT(D3, encodingStyle, D3 == encodingStyle);

            const T4& encodeEmptyArrays = X.encodeEmptyArrays();
            LOOP2_ASSERT(D4, encodeEmptyArrays, D4 == encodeEmptyArrays);

            const T5& encodeNullElements = X.encodeNullElements();
            LOOP2_ASSERT(D5, encodeNullElements, D5 == encodeNullElements);
        }

        if (verbose) cout <<
            "\nApply primary manipulators and verify expected values." << endl;

        if (veryVerbose) { T_ Q(initialIndentLevel) }
        {
            mX.setInitialIndentLevel(A1);

            const T1& initialIndentLevel = X.initialIndentLevel();
            LOOP2_ASSERT(A1, initialIndentLevel, A1 == initialIndentLevel);
        }

        if (veryVerbose) { T_ Q(spacesPerLevel) }
        {
            mX.setSpacesPerLevel(A2);

            const T2& spacesPerLevel = X.spacesPerLevel();
            LOOP2_ASSERT(A2, spacesPerLevel, A2 == spacesPerLevel);
        }

        if (veryVerbose) { T_ Q(encodingStyle) }
        {
            mX.setEncodingStyle(A3);

            const T3& encodingStyle = X.encodingStyle();
            LOOP2_ASSERT(A3, encodingStyle, A3 == encodingStyle);
        }

        if (veryVerbose) { T_ Q(encodeEmptyArrays) }
        {
            mX.setEncodeEmptyArrays(A4);

            const T4& encodeEmptyArrays = X.encodeEmptyArrays();
            LOOP2_ASSERT(A4, encodeEmptyArrays, A4 == encodeEmptyArrays);
        }

        if (veryVerbose) { T_ Q(encodeNullElements) }
        {
            mX.setEncodeNullElements(A5);

            const T5& encodeNullElements = X.encodeNullElements();
            LOOP2_ASSERT(A4, encodeNullElements, A4 == encodeNullElements);
        }
      } break;
      case 3: {
        // --------------------------------------------------------------------
        // TESTING MANIPULATORS
        //
        // Concerns:
        //: 1 Any argument can be 'const'.
        //:
        //: 2 Each attribute is modifiable independently.
        //:
        //: 3 Each attribute can be set to represent any value that does not
        //:   violate that attribute's documented constraints.
        //:
        //: 4 QoI: Asserted precondition violations are detected when enabled.
        //
        // Plan:
        //: 1 Create three sets of attribute values for the object: 'D', 'A',
        //:   and 'B'.  'D' values correspond to the attribute values, and 'A'
        //:   and 'B' values are chosen to be distinct boundary values where
        //:   possible.
        //:
        //: 2 Use the default constructor to create an object 'X'.
        //:
        //: 3 For each attribute 'i', in turn, create a local block.  Then
        //:   inside the block, using brute force, set that attribute's
        //:   value, passing a 'const' argument representing each of the
        //:   three test values, in turn (see P-1), first to 'Ai', then to
        //:   'Bi', and finally back to 'Di'.  After each transition, use the
        //:   (as yet unproven) basic accessors to verify that only the
        //:   intended attribute value changed.  (C-1, 3)
        //:
        //: 4 Corroborate that attributes are modifiable independently by
        //:   first setting all of the attributes to their 'A' values.  Then
        //:   incrementally set each attribute to its 'B' value and verify
        //:   after each manipulation that only that attribute's value
        //:   changed.  (C-2)
        //:
        //: 5 Verify that, in appropriate build modes, defensive checks are
        //:   triggered for invalid attribute values, but not triggered for
        //:   adjacent valid ones (using the 'BSLS_ASSERTTEST_*' macros).
        //:   (C-4)
        //
        // Testing:
        //   setInitialIndentLevel(int value);
        //   setSpacesPerLevel(int value);
        //   setEncodingStyle(Style value);
        //   setEncodeEmptyArrays(bool value);
        //   setEncodeNullElements(bool value);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING MANIPULATORS" << endl
                          << "====================" << endl;

        if (verbose) cout << "\nEstablish suitable attribute values." << endl;

        // 'D' values: These are the default-constructed values.

        const int   D1   = 0;                    // 'initialIndentLevel'
        const int   D2   = 0;                    // 'spacesPerLevel'
        const Style D3   = Obj::e_COMPACT;  // 'encodingStyle'
        const bool  D4   = false;                // 'encodeEmptyArrays'
        const bool  D5   = false;                // 'encodeNullElements'

        // 'A' values.

        const int   A1   = 1;                    // 'initialIndentLevel'
        const int   A2   = 4;                    // 'spacesPerLevel'
        const Style A3   = Obj::e_PRETTY;   // 'encodingStyle'
        const bool  A4   = true;                 // 'encodeEmptyArrays'
        const bool  A5   = true;                 // 'encodeNullElements'

        // 'B' values.

        const int   B1   = INT_MAX;               // 'initialIndentLevel'
        const int   B2   = INT_MAX;               // 'spacesPerLevel'
        const Style B3   = Obj::e_COMPACT;   // 'encodingStyle'
        const bool  B4   = false;                 // 'encodeEmptyArrays'
        const bool  B5   = false;                 // 'encodeNullElements'

        Obj mX;  const Obj& X = mX;

        if (verbose) cout <<
               "Verify that each attribute is independently settable." << endl;

        // --------------------
        // 'initialIndentLevel'
        // --------------------
        {
            mX.setInitialIndentLevel(A1);
            ASSERT(A1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setInitialIndentLevel(B1);
            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setInitialIndentLevel(D1);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());
        }

        // ----------------
        // 'spacesPerLevel'
        // ----------------
        {
            mX.setSpacesPerLevel(A2);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(A2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setSpacesPerLevel(B2);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(B2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setSpacesPerLevel(D2);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());
        }

        // ---------------
        // 'encodingStyle'
        // ---------------
        {
            mX.setEncodingStyle(A3);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(A3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setEncodingStyle(B3);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(B3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setEncodingStyle(D3);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());
        }

        // -------------------
        // 'encodeEmptyArrays'
        // -------------------
        {
            mX.setEncodeEmptyArrays(A4);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(A4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setEncodeEmptyArrays(B4);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(B4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());

            mX.setEncodeEmptyArrays(D4);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());
        }

        // --------------------
        // 'encodeNullElements'
        // --------------------
        {
            mX.setEncodeNullElements(A5);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

            mX.setEncodeNullElements(B5);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(B5 == X.encodeNullElements());

            mX.setEncodeNullElements(D5);
            ASSERT(D1 == X.initialIndentLevel());
            ASSERT(D2 == X.spacesPerLevel());
            ASSERT(D3 == X.encodingStyle());
            ASSERT(D4 == X.encodeEmptyArrays());
            ASSERT(D5 == X.encodeNullElements());
        }

        if (verbose) cout << "Corroborate attribute independence." << endl;
        {
            // ---------------------------------------
            // Set all attributes to their 'A' values.
            // ---------------------------------------

            mX.setInitialIndentLevel(A1);
            mX.setSpacesPerLevel(A2);
            mX.setEncodingStyle(A3);
            mX.setEncodeEmptyArrays(A4);
            mX.setEncodeNullElements(A5);

            ASSERT(A1 == X.initialIndentLevel());
            ASSERT(A2 == X.spacesPerLevel());
            ASSERT(A3 == X.encodingStyle());
            ASSERT(A4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

                 // ---------------------------------------
                 // Set all attributes to their 'B' values.
                 // ---------------------------------------

            mX.setInitialIndentLevel(B1);

            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(A2 == X.spacesPerLevel());
            ASSERT(A3 == X.encodingStyle());
            ASSERT(A4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

            mX.setSpacesPerLevel(B2);

            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(B2 == X.spacesPerLevel());
            ASSERT(A3 == X.encodingStyle());
            ASSERT(A4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

            mX.setEncodingStyle(B3);

            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(B2 == X.spacesPerLevel());
            ASSERT(B3 == X.encodingStyle());
            ASSERT(A4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

            mX.setEncodeEmptyArrays(B4);

            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(B2 == X.spacesPerLevel());
            ASSERT(B3 == X.encodingStyle());
            ASSERT(B4 == X.encodeEmptyArrays());
            ASSERT(A5 == X.encodeNullElements());

            mX.setEncodeNullElements(B5);

            ASSERT(B1 == X.initialIndentLevel());
            ASSERT(B2 == X.spacesPerLevel());
            ASSERT(B3 == X.encodingStyle());
            ASSERT(B4 == X.encodeEmptyArrays());
            ASSERT(B5 == X.encodeNullElements());
        }

        if (verbose) cout << "\nNegative Testing." << endl;
        {
            bsls::AssertFailureHandlerGuard
                                          hG(bsls::AssertTest::failTestDriver);

            Obj obj;

            if (veryVerbose) cout << "\tInitialIndentLevel" << endl;
            {
                ASSERT_SAFE_FAIL(obj.setInitialIndentLevel(-1));
                ASSERT_SAFE_PASS(obj.setInitialIndentLevel( 0));
            }

            if (veryVerbose) cout << "\tSpacesPerLevel" << endl;
            {
                ASSERT_SAFE_FAIL(obj.setSpacesPerLevel(-1));
                ASSERT_SAFE_PASS(obj.setSpacesPerLevel( 0));
            }
        }
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // TESTING CREATORS
        //
        // Concerns:
        //: 1 An object created with the default constructor has the
        //:   contractually specified default value.
        //
        // Plan:
        //: 1 Use the default constructor to create an object 'X'.
        //:
        //: 2 Use the individual (as yet unproven) salient attribute
        //:   accessors to verify the default-constructed value.  (C-1)
        //
        // Testing:
        //   baljsn::EncoderOptions();
        //   ~baljsn::EncoderOptions();
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING CREATORS" << endl
                          << "================" << endl;

        if (verbose) cout << "\nEstablish suitable attribute values." << endl;

        // 'D' values: These are the default-constructed values.

        const int   D1   = 0;                    // 'initialIndentLevel'
        const int   D2   = 0;                    // 'spacesPerLevel'
        const Style D3   = Obj::e_COMPACT;  // 'encodingStyle'
        const bool  D4   = false;                // 'encodeEmptyArrays'
        const bool  D5   = false;                // 'encodeNullElements'

        if (verbose) cout <<
                     "Create an object using the default constructor." << endl;

        Obj mX;  const Obj& X = mX;

        if (verbose) cout << "Verify the object's attribute values." << endl;

                  // -------------------------------------
                  // Verify the object's attribute values.
                  // -------------------------------------

        LOOP2_ASSERT(D1, X.initialIndentLevel(), D1 == X.initialIndentLevel());
        LOOP2_ASSERT(D2, X.spacesPerLevel(),     D2 == X.spacesPerLevel());
        LOOP2_ASSERT(D3, X.encodingStyle(),      D3 == X.encodingStyle());
        LOOP2_ASSERT(D4, X.encodeEmptyArrays(),  D4 == X.encodeEmptyArrays());
        LOOP2_ASSERT(D5, X.encodeNullElements(), D5 == X.encodeNullElements());

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //   This case exercises (but does not fully test) basic functionality.
        //
        // Concerns:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases.
        //
        // Plan:
        //: 1 Create an object 'w' (default ctor).       { w:D             }
        //: 2 Create an object 'x' (copy from 'w').      { w:D x:D         }
        //: 3 Set 'x' to 'A' (value distinct from 'D').  { w:D x:A         }
        //: 4 Create an object 'y' (init. to 'A').       { w:D x:A y:A     }
        //: 5 Create an object 'z' (copy from 'y').      { w:D x:A y:A z:A }
        //: 6 Set 'z' to 'D' (the default value).        { w:D x:A y:A z:D }
        //: 7 Assign 'w' from 'x'.                       { w:A x:A y:A z:D }
        //: 8 Assign 'w' from 'z'.                       { w:D x:A y:A z:D }
        //: 9 Assign 'x' from 'x' (aliasing).            { w:D x:A y:A z:D }
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "BREATHING TEST" << endl
                          << "==============" << endl;

        // Attribute Types

        typedef int   T1;        // 'initialIndentLevel'
        typedef int   T2;        // 'spacesPerLevel'
        typedef Style T3;        // 'encodingStyle'
        typedef bool  T4;        // 'encodeEmptyArrays'
        typedef bool  T5;        // 'encodeNullElements'
        typedef int   T6;        // 'datetimeFractionalSecondPrecision'

        // Attribute 1 Values: 'initialIndentLevel'

        const T1 D1 = 0;        // default value
        const T1 A1 = 4;

        // Attribute 2 Values: 'spacesPerLevel'

        const T2 D2 = 0;        // default value
        const T2 A2 = 10;

        // Attribute 3 Values: 'encodingStyle'

        const T3 D3 = Obj::e_COMPACT;    // default value
        const T3 A3 = Obj::e_PRETTY;

        // Attribute 4 Values: 'encodeEmptyArrays'

        const T4 D4 = false;    // default value
        const T4 A4 = true;

        // Attribute 5 Values: 'encodeNullElements'

        const T5 D5 = false;    // default value
        const T5 A5 = true;

        // Attribute 6 Values: 'datetimeFractionalSecondPrecision'

        const T6 D6 = 3;    // default value
        const T6 A6 = 6;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 1. Create an object 'w' (default ctor)."
                             "\t\t{ w:D             }" << endl;

        Obj mW;  const Obj& W = mW;

        if (veryVerbose) cout << "\ta. Check initial value of 'w'." << endl;
        if (veryVeryVerbose) { T_ T_ P(W) }

        ASSERT(D1 == W.initialIndentLevel());
        ASSERT(D2 == W.spacesPerLevel());
        ASSERT(D3 == W.encodingStyle());
        ASSERT(D4 == W.encodeEmptyArrays());
        ASSERT(D5 == W.encodeNullElements());
        ASSERT(D6 == W.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
                  "\tb. Try equality operators: 'w' <op> 'w'." << endl;

        ASSERT(1 == (W == W));        ASSERT(0 == (W != W));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 2. Create an object 'x' (copy from 'w')."
                             "\t\t{ w:D x:D         }" << endl;

        Obj mX(W);  const Obj& X = mX;

        if (veryVerbose) cout << "\ta. Check initial value of 'x'." << endl;
        if (veryVeryVerbose) { T_ T_ P(X) }

        ASSERT(D1 == X.initialIndentLevel());
        ASSERT(D2 == X.spacesPerLevel());
        ASSERT(D3 == X.encodingStyle());
        ASSERT(D4 == X.encodeEmptyArrays());
        ASSERT(D5 == X.encodeNullElements());
        ASSERT(D6 == X.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
                   "\tb. Try equality operators: 'x' <op> 'w', 'x'." << endl;

        ASSERT(1 == (X == W));        ASSERT(0 == (X != W));
        ASSERT(1 == (X == X));        ASSERT(0 == (X != X));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 3. Set 'x' to 'A' (value distinct from 'D')."
                             "\t\t{ w:D x:A         }" << endl;

        mX.setInitialIndentLevel(A1);
        mX.setSpacesPerLevel(A2);
        mX.setEncodingStyle(A3);
        mX.setEncodeEmptyArrays(A4);
        mX.setEncodeNullElements(A5);
        mX.setDatetimeFractionalSecondPrecision(A6);

        if (veryVerbose) cout << "\ta. Check new value of 'x'." << endl;
        if (veryVeryVerbose) { T_ T_ P(X) }

        ASSERT(A1 == X.initialIndentLevel());
        ASSERT(A2 == X.spacesPerLevel());
        ASSERT(A3 == X.encodingStyle());
        ASSERT(A4 == X.encodeEmptyArrays());
        ASSERT(A5 == X.encodeNullElements());
        ASSERT(A6 == X.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
             "\tb. Try equality operators: 'x' <op> 'w', 'x'." << endl;

        ASSERT(0 == (X == W));        ASSERT(1 == (X != W));
        ASSERT(1 == (X == X));        ASSERT(0 == (X != X));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 4. Create an object 'y' (init. to 'A')."
                             "\t\t{ w:D x:A y:A     }" << endl;

        Obj mY;  const Obj& Y = mY;
        mY.setInitialIndentLevel(A1);
        mY.setSpacesPerLevel(A2);
        mY.setEncodingStyle(A3);
        mY.setEncodeEmptyArrays(A4);
        mY.setEncodeNullElements(A5);
        mY.setDatetimeFractionalSecondPrecision(A6);

        if (veryVerbose) cout << "\ta. Check initial value of 'y'." << endl;
        if (veryVeryVerbose) { T_ T_ P(Y) }

        ASSERT(A1 == Y.initialIndentLevel());
        ASSERT(A2 == Y.spacesPerLevel());
        ASSERT(A3 == Y.encodingStyle());
        ASSERT(A4 == Y.encodeEmptyArrays());
        ASSERT(A5 == Y.encodeNullElements());
        ASSERT(A6 == Y.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
             "\tb. Try equality operators: 'y' <op> 'w', 'x', 'y'" << endl;

        ASSERT(0 == (Y == W));        ASSERT(1 == (Y != W));
        ASSERT(1 == (Y == X));        ASSERT(0 == (Y != X));
        ASSERT(1 == (Y == Y));        ASSERT(0 == (Y != Y));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 5. Create an object 'z' (copy from 'y')."
                             "\t\t{ w:D x:A y:A z:A }" << endl;

        Obj mZ(Y);  const Obj& Z = mZ;

        if (veryVerbose) cout << "\ta. Check initial value of 'z'." << endl;
        if (veryVeryVerbose) { T_ T_ P(Z) }

        ASSERT(A1 == Z.initialIndentLevel());
        ASSERT(A2 == Z.spacesPerLevel());
        ASSERT(A3 == Z.encodingStyle());
        ASSERT(A4 == Z.encodeEmptyArrays());
        ASSERT(A5 == Z.encodeNullElements());
        ASSERT(A6 == Z.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
           "\tb. Try equality operators: 'z' <op> 'w', 'x', 'y', 'z'." << endl;

        ASSERT(0 == (Z == W));        ASSERT(1 == (Z != W));
        ASSERT(1 == (Z == X));        ASSERT(0 == (Z != X));
        ASSERT(1 == (Z == Y));        ASSERT(0 == (Z != Y));
        ASSERT(1 == (Z == Z));        ASSERT(0 == (Z != Z));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 6. Set 'z' to 'D' (the default value)."
                             "\t\t\t{ w:D x:A y:A z:D }" << endl;

        mZ.setInitialIndentLevel(D1);
        mZ.setSpacesPerLevel(D2);
        mZ.setEncodingStyle(D3);
        mZ.setEncodeEmptyArrays(D4);
        mZ.setEncodeNullElements(D5);
        mZ.setDatetimeFractionalSecondPrecision(D6);

        if (veryVerbose) cout << "\ta. Check new value of 'z'." << endl;
        if (veryVeryVerbose) { T_ T_ P(Z) }

        ASSERT(D1 == Z.initialIndentLevel());
        ASSERT(D2 == Z.spacesPerLevel());
        ASSERT(D3 == Z.encodingStyle());
        ASSERT(D4 == Z.encodeEmptyArrays());
        ASSERT(D5 == Z.encodeNullElements());
        ASSERT(D6 == Z.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
           "\tb. Try equality operators: 'z' <op> 'w', 'x', 'y', 'z'." << endl;

        ASSERT(1 == (Z == W));        ASSERT(0 == (Z != W));
        ASSERT(0 == (Z == X));        ASSERT(1 == (Z != X));
        ASSERT(0 == (Z == Y));        ASSERT(1 == (Z != Y));
        ASSERT(1 == (Z == Z));        ASSERT(0 == (Z != Z));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 7. Assign 'w' from 'x'."
                             "\t\t\t\t{ w:A x:A y:A z:D }" << endl;
        mW = X;

        if (veryVerbose) cout << "\ta. Check new value of 'w'." << endl;
        if (veryVeryVerbose) { T_ T_ P(W) }

        ASSERT(A1 == W.initialIndentLevel());
        ASSERT(A2 == W.spacesPerLevel());
        ASSERT(A3 == W.encodingStyle());
        ASSERT(A4 == W.encodeEmptyArrays());
        ASSERT(A5 == W.encodeNullElements());
        ASSERT(A6 == W.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
           "\tb. Try equality operators: 'w' <op> 'w', 'x', 'y', 'z'." << endl;

        ASSERT(1 == (W == W));        ASSERT(0 == (W != W));
        ASSERT(1 == (W == X));        ASSERT(0 == (W != X));
        ASSERT(1 == (W == Y));        ASSERT(0 == (W != Y));
        ASSERT(0 == (W == Z));        ASSERT(1 == (W != Z));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 8. Assign 'w' from 'z'."
                             "\t\t\t\t{ w:D x:A y:A z:D }" << endl;
        mW = Z;

        if (veryVerbose) cout << "\ta. Check new value of 'w'." << endl;
        if (veryVeryVerbose) { T_ T_ P(W) }

        ASSERT(D1 == W.initialIndentLevel());
        ASSERT(D2 == W.spacesPerLevel());
        ASSERT(D3 == W.encodingStyle());
        ASSERT(D4 == W.encodeEmptyArrays());
        ASSERT(D5 == W.encodeNullElements());
        ASSERT(D6 == W.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
           "\tb. Try equality operators: 'x' <op> 'w', 'x', 'y', 'z'." << endl;

        ASSERT(1 == (W == W));        ASSERT(0 == (W != W));
        ASSERT(0 == (W == X));        ASSERT(1 == (W != X));
        ASSERT(0 == (W == Y));        ASSERT(1 == (W != Y));
        ASSERT(1 == (W == Z));        ASSERT(0 == (W != Z));

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (verbose) cout << "\n 9. Assign 'x' from 'x' (aliasing)."
                             "\t\t\t{ w:D x:A y:A z:D }" << endl;
        mX = X;

        if (veryVerbose) cout << "\ta. Check (same) value of 'x'." << endl;
        if (veryVeryVerbose) { T_ T_ P(X) }

        ASSERT(A1 == X.initialIndentLevel());
        ASSERT(A2 == X.spacesPerLevel());
        ASSERT(A3 == X.encodingStyle());
        ASSERT(A4 == X.encodeEmptyArrays());
        ASSERT(A5 == X.encodeNullElements());
        ASSERT(A6 == X.datetimeFractionalSecondPrecision());

        if (veryVerbose) cout <<
           "\tb. Try equality operators: 'x' <op> 'w', 'x', 'y', 'z'." << endl;

        ASSERT(0 == (X == W));        ASSERT(1 == (X != W));
        ASSERT(1 == (X == X));        ASSERT(0 == (X != X));
        ASSERT(1 == (X == Y));        ASSERT(0 == (X != Y));
        ASSERT(0 == (X == Z));        ASSERT(1 == (X != Z));

      } break;
      default: {
        bsl::cerr << "WARNING: CASE `" << test << "' NOT FOUND." << bsl::endl;
        testStatus = -1;
      }
    }

    LOOP_ASSERT(globalAllocator.numBlocksTotal(),
                0 == globalAllocator.numBlocksTotal());

    LOOP_ASSERT(defaultAllocator.numBlocksTotal(),
                0 == defaultAllocator.numBlocksTotal());

    if (testStatus > 0) {
        bsl::cerr << "Error, non-zero test status = " << testStatus << "."
                  << bsl::endl;
    }
    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
