using System;
using System.Collections.Generic;
using System.Text;

namespace Ambiesoft
{
    public enum ARGUMENT_TYPE
    {
        MUST,
        MUSTNOT,
        BOTH,
    }

    class ArgumentInfo
    {
        public ArgumentInfo(ARGUMENT_TYPE argType, String description)
        {
            argType_ = argType;
            description_ = description;
        }

        public readonly ARGUMENT_TYPE argType_;
        public readonly String description_;
    };

    public class SimpleCommandLineParser
    {
        private String[] args_;
        private Dictionary<String, ArgumentInfo> def_validops_ = new Dictionary<string, ArgumentInfo>();
        private Dictionary<String, Object> in_validops_ = new Dictionary<string, object>();
        private List<String> in_invalidops_ = new List<string>();
        private List<String> mainargs_ = new List<string>();

        private bool isOptionLeft(String s)
        {
            return (s.StartsWith("/") || s.StartsWith("-"));
        }

        public SimpleCommandLineParser(String[] args)
        {
            args_ = args;
        }

        public void addOption(String option, ARGUMENT_TYPE argType, String description)
        {
            ArgumentInfo ai = new ArgumentInfo(argType, description);
            def_validops_[option] = ai;
        }
        public void addOption(String option, ARGUMENT_TYPE hasArgument)
        {
            addOption(option, hasArgument, "");
        }

        public void Parse()
        {
            if (args_ == null)
                return;

            for (int i = 0; i < args_.Length; ++i)
            {
                String s = args_[i];
                if (isOptionLeft(s))
                {
                    s = s.TrimStart(new char[] { '/', '-' });

                    // ARGUMENT_TYPE inv;
                    ArgumentInfo ai;
                    if (!def_validops_.TryGetValue(s, out ai))
                    {
                        in_invalidops_.Add(s);
                    }
                    else
                    {
                        // valid option
                        if (ai.argType_ == ARGUMENT_TYPE.MUSTNOT)
                        {
                            in_validops_[s] = true;
                        }
                        else
                        {
                            if (args_.Length > (i + 1))
                            {
                                if (!isOptionLeft(args_[i + 1]))
                                {
                                    in_validops_[s] = args_[i + 1];
                                    ++i;
                                }
                            }
                            else
                            {
                                if (ai.argType_ == ARGUMENT_TYPE.MUST)
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

        public Object this[String s]
        {
            get
            {
                Object ret;
                in_validops_.TryGetValue(s, out ret);
                return ret;
            }
        }



        public String getMainargs(int i)
        {
            return mainargs_[i];
        }

        public int MainargLength
        {
            get
            {
                return mainargs_.Count;
            }
        }

        public String[] getInvalidOptions()
        {
            return in_invalidops_.ToArray();
        }

        public String HelpString
        {
            get
            {
                System.Text.StringBuilder sb = new StringBuilder();
                foreach (KeyValuePair<String, ArgumentInfo> kv in def_validops_)
                // for each( KeyValuePair<String^, ArgumentInfo^> kv in def_validops_)
                {
                    sb.Append("/");
                    sb.Append(kv.Key);
                    if (kv.Value.argType_ == ARGUMENT_TYPE.BOTH)
                    {
                        sb.Append(" [arg] : ");
                    }
                    else if (kv.Value.argType_ == ARGUMENT_TYPE.MUST)
                    {
                        sb.Append(" arg : ");
                    }
                    else
                    {
                        sb.Append(" : ");
                    }
                    sb.Append(kv.Value.description_);
                    sb.AppendLine();
                }

                return sb.ToString();
            }
        }

        public String DebugOutput()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("valid optioins:");
            foreach (KeyValuePair<String, Object> kv in in_validops_)
            {
                sb.Append(kv.Key);
                sb.Append(" : ");
                sb.Append(kv.Value);
                sb.AppendLine();
            }

            sb.AppendLine();
            sb.AppendLine("invalid options:");
            foreach (String s in in_invalidops_)
            {
                sb.AppendLine(s);
            }

            sb.AppendLine();
            sb.AppendLine("main args:");
            foreach (String m in mainargs_)
            {
                sb.AppendLine(m);
            }

            return sb.ToString();
        }
    }
}
