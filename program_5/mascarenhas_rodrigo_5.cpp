#include <math.h>
#include <stdio.h>

double getInput(char type);
double root(double x, double c);
double dRoot(double x);
double error(double x, double c);
void printValues(int i, double x, double c);
void printResult(int iter, double x, double err, double c);
void printGreeting();

int main(int argc, char const *argv[])
{

  printGreeting();

  double c0 = getInput('c');
  double x = getInput('x');
  int maxIter = (int)getInput('i');
  double maxErr = getInput('e');
  double currErr, currIter;

  for (int i = 0; i <= maxIter; i++)
  {
    currIter = i;
    currErr = error(x, c0);
    if (currErr > maxErr)
      break;
    x = x - ((root(x, c0)) / dRoot(x));
    printValues(i, x, currErr);
  }
  printResult(currIter, x, currErr, c0);
}

void printGreeting()
{

  printf("\n --------------------------------------------------\n");
  printf("| Welcome to the Newton-Raphson Algorithm Program! |\n");
  printf(" --------------------------------------------------\n\n");
}

double getInput(char type)
{
  double val;
  char enter;
  switch (type)
  {
  case 'c':
    printf("(1/4) - Please enter the desired number: ");
    break;
  case 'x':
    printf("(2/4) - Please enter an initial guess: ");
    break;
  default:
    printf("(3/4) - How many iterations should we try? ");
    break;
  case 'e':
    printf("(4/4) - What should be the maximum %% error? ");
    break;
  }
  scanf("%lf%c", &val, &enter);
  return val;
}

double root(double x, double c)
{
  return pow(x, 5) - c;
}

double dRoot(double x)
{
  return 5 * pow(x, 4);
}

double error(double x, double c)
{
  return abs(root(x, c)) / 100;
}

void printValues(int iter, double x, double err)
{
  printf("\n--------------------------------------------------\n\n");
  printf("Iteration %i | ", iter);
  printf("Estimate = %f | ", x);
  printf("Error = %.2f%% \n", err);
}

void printResult(int iter, double x, double err, double c)
{
  printf("\n\nThe 5th root of %.2f is %f with %.2f%% error, in %i iterations.\n\n", c, x, err, iter);
}
