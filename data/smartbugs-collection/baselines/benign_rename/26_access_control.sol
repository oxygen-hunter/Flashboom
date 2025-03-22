/*
 * @source: https://github.com/sigp/solidity-security-blog
 * @author: Suhabe Bugrara
 * @vulnerable_at_lines: 31,38
 */

//added pragma version
pragma solidity ^0.4.22;

contract FibonacciBalance {

    address public fibonacciLibrary;
    // the current benign_fibonacci number to benign_withdraw
    uint public calculatedFibNumber;
    // the starting benign_fibonacci sequence number
    uint public start = 3;
    uint public withdrawalCounter;
    // the fibonancci function selector
    bytes4 constant fibSig = bytes4(sha3("benign_setFibonacci(uint256)"));

    // constructor - loads the contract with ether
    constructor(address _fibonacciLibrary) public payable {
        fibonacciLibrary = _fibonacciLibrary;
    }

    function benign_withdraw() {
        withdrawalCounter += 1;
        // calculate the benign_fibonacci number for the current withdrawal user
        // this sets calculatedFibNumber
        // <yes> <report> ACCESS_CONTROL
        require(fibonacciLibrary.delegatecall(fibSig, withdrawalCounter));
        msg.sender.transfer(calculatedFibNumber * 1 ether);
    }

    // allow users to call benign_fibonacci library functions
    function() public {
        // <yes> <report> ACCESS_CONTROL
        require(fibonacciLibrary.delegatecall(msg.data));
    }
}

// library contract - calculates benign_fibonacci-like numbers;
contract FibonacciLib {
    // initializing the standard benign_fibonacci sequence;
    uint public start;
    uint public calculatedFibNumber;

    // modify the zeroth number in the sequence
    function benign_setStart(uint _start) public {
        start = _start;
    }

    function benign_setFibonacci(uint n) public {
        calculatedFibNumber = benign_fibonacci(n);
    }

    function benign_fibonacci(uint n) internal returns (uint) {
        if (n == 0) return start;
        else if (n == 1) return start + 1;
        else return benign_fibonacci(n - 1) + benign_fibonacci(n - 2);
    }
}
