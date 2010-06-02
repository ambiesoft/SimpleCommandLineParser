// SimpleCommandLineParser.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Ambiesoft {

	public enum class ARGUMENT_TYPE
	{
		MUST,
		MUSTNOT,
		BOTH,
	};

	private ref class ArgumentInfo
	{
	public:
		ArgumentInfo(ARGUMENT_TYPE argType, String^ description)
		{
			argType_ = argType;
			description_ = description;
		}

		initonly ARGUMENT_TYPE argType_;
		initonly String^ description_;
	};

	public ref class SimpleCommandLineParser
	{
	private:
		array<String^>^ args_;
		Dictionary<String^,ArgumentInfo^> def_validops_;
		Dictionary<String^,Object^> in_validops_;
		List<String^> in_invalidops_;
		List<String^> mainargs_;

		bool isOptionLeft(String^ s)
		{
			return ( s->StartsWith("/") || s->StartsWith("-") );
		}

	public:
		SimpleCommandLineParser(array<String^>^ args)
		{
			args_=args;
		}

		/***
		* 
		*/
		void addOption(String^ option, ARGUMENT_TYPE argType, String^ description)
		{
			ArgumentInfo^ ai = gcnew ArgumentInfo(argType, description);
			def_validops_[option] = ai;
		}
		void addOption(String^ option, ARGUMENT_TYPE hasArgument)
		{
			addOption(option, hasArgument, L"");
		}

		void Parse()
		{
			if ( args_ == nullptr )
				return;

			for ( int i=0 ; i < args_->Length ; ++i )
			{
				String^ s = args_[i];
				if ( isOptionLeft(s) )
				{
					s = s->TrimStart(gcnew array<Char>{'/','-'});

					// ARGUMENT_TYPE inv;
					ArgumentInfo^ ai;
					if(!def_validops_.TryGetValue(s, ai))
					{
						in_invalidops_.Add(s);
					}
					else
					{
						// valid option
						if(ai->argType_==ARGUMENT_TYPE::MUSTNOT)
						{
							in_validops_[s] = true;
						}
						else
						{
							if ( args_->Length > (i+1) )
							{
								if ( !isOptionLeft(args_[i+1]) )
								{
									in_validops_[s] = args_[i+1];
									++i;
								}
							}
							else
							{
								if(ai->argType_==ARGUMENT_TYPE::MUST)
								{
									in_validops_[s] = "";
								}
								else
								{
									in_validops_[s] = true;
								}
							}
						}
					}
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
				Object^ ret;
				in_validops_.TryGetValue(s,ret);
				return ret;
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

		array<String^>^ getInvalidOptions()
		{
			return in_invalidops_.ToArray();
		}

		property String^ HelpString
		{
			String^ get()
			{
				System::Text::StringBuilder sb;
				for each( KeyValuePair<String^, ArgumentInfo^> kv in def_validops_)
				{
					sb.Append(L"/");
					sb.Append(kv.Key);
					if ( kv.Value->argType_==ARGUMENT_TYPE::BOTH )
					{
						sb.Append(L" [arg] : ");
					}
					else if ( kv.Value->argType_==ARGUMENT_TYPE::MUST )
					{
						sb.Append(L" arg : ");
					}
					else
					{
						sb.Append(L" : ");
					}
					sb.Append(kv.Value->description_);
					sb.AppendLine();
				}

				return sb.ToString();
			}
		}

		String^ DebugOutput()
		{
			System::Text::StringBuilder sb;
			sb.AppendLine("valid optioins:");
			for each(KeyValuePair<String^,Object^> kv in in_validops_)
			{
				sb.Append(kv.Key);
				sb.Append(" : ");
				sb.Append(kv.Value);
				sb.AppendLine();
			}
			
			sb.AppendLine();
			sb.AppendLine("invalid options:");
			for each(String^ s in in_invalidops_)
			{
				sb.AppendLine(s);
			}

			sb.AppendLine();
			sb.AppendLine("main args:");
			for each(String^ m in mainargs_)
			{
				sb.AppendLine(m);
			}

			return sb.ToString();
		}
	};
}
