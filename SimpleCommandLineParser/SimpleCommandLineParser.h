// SimpleCommandLineParser.h

#pragma once

using namespace System;

namespace Ambiesoft {

	public ref class SimpleCommandLineParser
	{
	private:
		System::Collections::Hashtable hashes_;
		System::Collections::Generic::List<String^> mainargs_;

		bool isOptionLeft(String^ s)
		{
			return ( s->StartsWith("/") || s->StartsWith("-") );
		}

	public:
		SimpleCommandLineParser(array<String^>^ args)
		{
			if ( args == nullptr )
				return;

			for ( int i=0 ; i < args->Length ; ++i )
			{
				String^ s = args[i];
				if ( isOptionLeft(s) )
				{
					s = s->TrimStart(gcnew array<Char>{'/','-'});
					bool determined = false;
					if ( args->Length > i )
					{
						if ( !isOptionLeft(args[i+1]) )
						{
							hashes_[s] = args[i+1];
							++i;
							determined = true;
						}
					}

					if ( !determined )
						hashes_[s] = true;
				}
				else
				{
					mainargs_.Add(s);
				}
			}
		}

		property Object^ default[String^]
		{
			Object^ get(String^ s)
			{
				return hashes_[s];
			}
		}

		property String^ Mainargs[int]
		{
			String^ get(int i)
			{
				return mainargs_[i];
			}
		}

		property int MainargLength
		{
			int get()
			{
				return mainargs_.Count;
			}
		}
	};
}
