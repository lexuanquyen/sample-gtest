#include "base/callback_list.h"

#include <memory>
#include <utility>

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/macros.h"
#include "testing/gtest/include/gtest/gtest.h"

#include "base/test/launcher/unit_test_launcher.h"
#include "base/test/test_suite.h"
#include "build/build_config.h"
#include <iostream>
namespace base{
	namespace {
		class Listener {
		public:
			Listener() :total_(0), scaler_(1) {
			}
			explicit Listener(int scaler) :total_(0), scaler_(scaler) {

			}
			void IncrementTotal() {
				total_++;
			}
			void IncrementByMultipleOfScaler(int x) {
				total_ += x* scaler_;
			}
		private:
			int total_;
			int scaler_;
			DISALLOW_COPY_AND_ASSIGN(Listener);
		};
	 class Summer {
	 public:
		 Summer():value_(0){
			 std::cout << "khoi tao Summer " << std::endl;
		 }
		 void AddOneParam(int a){
			 value_ = a;
		 }
		 void AddTwoParam(int a, int b) {
			 value_ = a + b;
		 }
		 void AddThreeParam(int a, int b, int c) {
			 value_ = a + b + c;
		 }
		 void AddFourParam(int a, int b, int c, int d) {
			 value_ = a + b + c + d;

		 }
		 void AddFiveParam(int a, int b, int c, int d, int e) {
			 value_ = a + b + c + d + e;
		 }
		 void AddSixParam(int a, int b, int c, int d, int e, int f) {
			 value_ = a + b + c + d + e + f;
		 }
		 int value() {
			 return value_;
		 }
	 private:
		 int value_;
		 DISALLOW_COPY_AND_ASSIGN(Summer);
	 };

	}
	
}
TEST(Summer, ArityTest) {
	base::Summer s;
	base::CallbackList<void(int)> c1;
	std::unique_ptr<base::CallbackList<void(int)>::Subscription> subscription1 =
		c1.Add(base::Bind(&base::Summer::AddOneParam, base::Unretained(&s)));
	c1.Notify(1);
	DLOG(INFO) << "KET QUA :";
	EXPECT_EQ(1, s.value());

	//std::cout << " One add : " << s.value() << std::endl;

	base::CallbackList<void(int, int) > c2;
	std::unique_ptr<base::CallbackList<void(int, int)>::Subscription> subscription2 =
		c2.Add(base::Bind(&base::Summer::AddTwoParam, base::Unretained(&s)));
	c2.Notify(1, 2);
	EXPECT_EQ(3, s.value());
	//std::cout << "Two add: " << s.value() << std::endl;
}

int main(int argc, char** argv) {
	
	base::TestSuite test_suite(argc, argv);
	
	 base::LaunchUnitTests(
		argc, argv,
		base::Bind(&base::TestSuite::Run, base::Unretained(&test_suite)));
	 getchar();
	 return 0;
}

