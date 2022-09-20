/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ada2020;

/**
 *
 * @author od
 */
public class ExerRec 
{
    public static int sum(int n)
    {
        if (n == 0)
            return 0;
        return n + sum(n-1);
    }
    public static long fib(int n)
    {
        if (n<= 1)
            return 1;
        else
            return fib(n-1) + fib(n-2);
    }
    
  public static int evenSquares(int n)
  {
      if (n == 0)
          return 0;
      return (4 * n * n) + evenSquares(n - 1);
  }
  
  
  public static boolean linear(String s,char c,int l)
  {
      if (l == 0)
        return false;
      if (s.charAt(l-1) == c)
        return true;
      return linear(s,c,l-1);
  }
  
    public static int binarySearch(int arr[], int value)
    {
        return binarySearch(arr,0,arr.length-1, value);
    }
    
    private static int binarySearch(int[] array, int start, int end, int target) 
    { 
        int middle = (start + end) / 2; 
        if (end < start) 
        { 
            return -1; 
        } 
        if (target == array[middle]) 
        { 
            return middle; 
        } 
        else if (target < array[middle]) 
        { 
            return binarySearch(array, start, middle - 1, target); 
        } 
        else 
        { 
            return binarySearch(array, middle + 1, end, target); 
        } 
    }

    
    public static void main(String ars[])
    {
        int[] arr = {2,4,6,8,11,14,76,99,101};
        System.out.println(binarySearch(arr,101));
    }
    
}
