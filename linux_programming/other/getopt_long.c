/*
程序功能描述：测试getopt_long的使用
*/

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
 
int
main(int argc, char **argv)
{
	int c;
	int digit_optind = 0;
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
		    {"add",     required_argument, 0,  0 },
		    {"append",  no_argument,       0,  1 },
		    {"delete",  required_argument, 0,  0 },
		    {"verbose", no_argument,       0,  0 }, //没有参数值
		    {"create",  required_argument, 0, 'c'},
		    {"file",    required_argument, 0,  0 }, //参数值必带，格式--xxx yyy或者 --xxx=yyy
		    {"visas",   optional_argument, 0,  2 }, //参数值可选，格式必须 --xxx=yyy或者 --xxx
		    {0,         0,                 0,  0 }
		};

		c = getopt_long(argc, argv, "abc:d:012g::", 
		         long_options, &option_index);
		if (c == -1){
			printf("option need \'-\' or \'--\'\n");
			break;
		}

		switch (c) {																
			case 0: //测试长选项
			printf("option %s", long_options[option_index].name);
			if (optarg)
			    printf(" with arg %s", optarg);
			printf("\n");
			break;
			
			case 1:	//测试--append
			printf("return 1, option %s", long_options[option_index].name);
			if (optarg)
			    printf(" with arg %s", optarg);
			printf("\n");
			break;

			case 2: //测试--visas
			printf("return 2, option %s", long_options[option_index].name);
			if (optarg)
			    printf(" with arg %s", optarg);
			printf("\n");
			break;
			
			break;
			case '0'://测试短选项
			case '1':
			case '2':
			if (digit_optind != 0 && digit_optind != this_option_optind)
			  printf("digits occur in two different argv-elements.\n");
			digit_optind = this_option_optind;
			printf("option %c\n", c);
			break;

			case 'a':
			printf("option a\n");
			break;

			case 'b':
			printf("option b\n");
			break;

			case 'c'://测试-c and --create
			printf("option c with value '%s'\n", optarg);
			break;

			case 'd':
			printf("option d with value '%s'\n", optarg);
			break;

			case 'g': 
			printf("option g");
			if (optarg)
			    printf(" with arg %s", optarg);
			printf("\n");
			break;

			case '?':		//选项有加-或者--，但是找不到该选项，或者选项没加参数值
			printf("not find, or need arg\n");
			break;
			default:
			printf("?? getopt returned character code 0%o ??\n", c);
		}
	}

	//printf("optind = %d argc = %d\n", optind,argc);
	if (optind < argc) {	//选项没有加-或者--
		printf("non-option ARGV-elements: ");
		while (optind < argc)
		    printf("%s ", argv[optind++]);
		printf("\n");
	}
 
   exit(EXIT_SUCCESS);
}

