using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGenerator
{
    class Program
    {
        enum ErrorCodes
        {
            ERROR = -1,
            SUCCESS = 0
        }

        enum CommandArguments
        {
            SOURCE_DIR = 0,
            DESTINATION_DIR,
            COUNT
        }

        const string ERROR_INVALID_NUMBER_PARAMS = "Invalid number of parameters. Expected: {0}, Received: {1}."
                                                    + "You need to specify the source directory and destination filename (along with an optional path).";

        static int Main(string[] args)
        {
            int NumberArgs = args.Length;
            if (NumberArgs != (int)CommandArguments.COUNT)
            {
                Console.Write(String.Format(ERROR_INVALID_NUMBER_PARAMS, (int)CommandArguments.COUNT, NumberArgs));
                return (int)ErrorCodes.ERROR;
            }

            try
            {
                FileConverter F = new FileConverter();
                F.Convert(args[(int)CommandArguments.SOURCE_DIR], args[(int)CommandArguments.DESTINATION_DIR]);
            }
            catch (Exception e)
            {
                Console.Write(e.Message);
                return (int)ErrorCodes.ERROR;
            }

            return (int)ErrorCodes.SUCCESS;
        }
    }
}
