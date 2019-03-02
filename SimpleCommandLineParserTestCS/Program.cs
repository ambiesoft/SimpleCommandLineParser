using Ambiesoft;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleCommandLineParserTestCS
{
    class Program
    {
        static int Main(string[] args)
        {
            SimpleCommandLineParser parser = new SimpleCommandLineParser(args);
            parser.addOption("rf", ARGUMENT_TYPE.MUST);
            parser.addOption("rt", ARGUMENT_TYPE.MUST);
            parser.addOption("ie", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("ic", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("cf", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("ca", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("blob", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("h", ARGUMENT_TYPE.MUSTNOT);
            parser.addOption("?", ARGUMENT_TYPE.MUSTNOT);
            parser.Parse();
            if (parser["h"] != null || parser["?"] != null)
            {
                return 0;
            }
            if (parser["ca"] != null)
            {
                // check argument
                StringBuilder sb = new StringBuilder();
                if (parser["rf"] != null)
                {
                    sb.Append("rf:");
                    sb.AppendLine(parser["rf"].ToString());
                }

                if (parser["rt"] != null)
                {
                    sb.Append("rt:");
                    sb.AppendLine(parser["rt"].ToString());
                }

                if (parser["ie"] != null)
                    sb.AppendLine("ie");
                if (parser["ic"] != null)
                    sb.AppendLine("ic");
                if (parser["ca"] != null)
                    sb.AppendLine("ca");
                if (parser["cf"] != null)
                    sb.AppendLine("cf");
                if (parser["blob"] != null)
                    sb.AppendLine("blob");
                if (parser["h"] != null)
                    sb.AppendLine("h");
                if (parser["?"] != null)
                    sb.AppendLine("?");

                sb.AppendLine("--------------");

                for (int i = 0; i < parser.MainargLength; ++i)
                    sb.AppendLine(parser.getMainargs(i));

                CppUtils.CenteredMessageBox(sb.ToString());
            }
             
            return 0;
            
        }

    }
}