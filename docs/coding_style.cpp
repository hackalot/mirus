// Copyright 2013 Mirus Project

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// coding_style.cpp - Follow this guide when working on the source
//

namespace mirus
{
	namespace coding_style
	{
		//
		// The most wonderful class ever
		//
		class MyClass
		{
		public:
			//
			// ctor
			// 
			MyClass();

			//
			// Function definition in class likewise
			// 
			void my_class_function(
				int value1, 
				int value2, 
				int value3,
				int value4,
				int value5
			);

		private:
			//
			// Member variables
			// 
			int m_variable;
			int m_var1;
		};

		//
		// Implements MyClass
		MyClass::MyClass()
		{
			// ...
		}

		//
		// Wrap long lines like so
		// 
		void MyClass::my_class_function(int value1, int value2, int value3,
				int value4,int value5)
		{
			// ...
		}
	} // !namespace
} // !namespace