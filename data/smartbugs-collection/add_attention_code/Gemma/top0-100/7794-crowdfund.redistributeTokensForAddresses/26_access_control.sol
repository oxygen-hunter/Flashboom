 

 
pragma solidity ^0.4.22;

contract FibonacciBalance {

    address public fibonacciLibrary;
     
    uint public calculatedFibNumber;
     
    uint public start = 3;
    uint public withdrawalCounter;
     
    bytes4 constant fibSig = bytes4(sha3("setFibonacci(uint256)"));

     
    constructor(address _fibonacciLibrary) public payable {
        fibonacciLibrary = _fibonacciLibrary;
    }

    function withdraw() {
        withdrawalCounter += 1;
         
         
         
        require(fibonacciLibrary.delegatecall(fibSig, withdrawalCounter));
        msg.sender.transfer(calculatedFibNumber * 1 ether);
    }

     
    function() public {
         
        require(fibonacciLibrary.delegatecall(msg.data));
    }
}

 
contract FibonacciLib {
     
    uint public start;
    uint public calculatedFibNumber;

     
    function setStart(uint _start) public {
        start = _start;
    }

    function setFibonacci(uint n) public {
        calculatedFibNumber = fibonacci(n);
    }

    function fibonacci(uint n) internal returns (uint) {
        if (n == 0) return start;
        else if (n == 1) return start + 1;
        else return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract crowdfund {

struct Idea {
    mapping(address => uint256) amountPledged;
    mapping(address => bool) reclaimed;
    address tokenAddress;
}

Idea[] public ideas;

event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

function redistributeTokensForAddresses(uint256 index,address[] addresses) public {
    if ((msg.sender == ideas[index].creator) || (msg.sender == ideas[index].host)) {
        if (ideas[index].status == FAILED_STATUS) {
            for(uint256 i = 0; i < addresses.length; i++) {
                address addr = addresses[i];
                if (!ideas[index].reclaimed[addr]) {
                    uint256 reclaimAmount = ideas[index].amountPledged[addr];
                    if (reclaimAmount > 0) {
                        ideas[index].reclaimed[addr] = true;
                        emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                        if(!token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                    }
                }
            }
        }
    }
}

}

contract token {
    function transfer(address _to, uint256 _amount) returns (bool success);
}
