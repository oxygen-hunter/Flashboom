 

 
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
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

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

contract ERC20Basic {
  uint256 public totalSupply;
  function balanceOf(address who) public constant returns (uint256);
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract BasicToken is ERC20Basic {
  using SafeMath for uint256;

  mapping(address => uint256) balances;

  function balanceOf(address _owner) public constant returns (uint256 balance) {
    return balances[_owner];
  }
}

contract StandardToken is BasicToken {}

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVCC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;
    
    balances[0x158CeaeEad026C6d0B18205ABF580d9AaD905520] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x158CeaeEad026C6d0B18205ABF580d9AaD905520, 320000000 * (10 ** uint256(decimals)));

    balances[0x7161431BfCECd83D45982fA1C6ed9878e2395468] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0x7161431BfCECd83D45982fA1C6ed9878e2395468, 480000000 * (10 ** uint256(decimals)));

    balances[0xE05A7C3f9A956B921F42dFf5B4eB8170E5C6b2FC] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xE05A7C3f9A956B921F42dFf5B4eB8170E5C6b2FC, 200000000 * (10 ** uint256(decimals)));
  }
}
