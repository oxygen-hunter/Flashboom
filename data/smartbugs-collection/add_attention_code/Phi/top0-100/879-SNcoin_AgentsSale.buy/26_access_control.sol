 

 
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

     

    MinimalTokenInterface public tokenContract;
    address public spenderAddress;
    address public vaultAddress;
    bool public fundingEnabled;
    uint public totalCollected;         // In wei
    TokenPriveProviderInterface public tokenPriceProvider;         // In wei
    mapping(address => address) agents;

    function buy(uint _discount, bytes _promocode) public payable {
        require (fundingEnabled);
        uint tokenPrice = tokenPriceProvider.tokenPrice(); // In wei
        require (tokenPrice > 10**9);
        require (msg.value >= tokenPrice);
        require (_discount <= 20);
        require (_promocode.length == 97);

        bytes32 r;
        bytes32 s;
        uint8 v;
        bytes32 h;
        assembly {
          r := mload(add(_promocode, 32))
          s := mload(add(_promocode, 64))
          v := and(mload(add(_promocode, 65)), 255)
          h := mload(add(_promocode, 97))
        }

        // https://github.com/ethereum/go-ethereum/issues/2053
        if (v < 27) {
          v += 27;
        }
        require ((v == 27) || (v == 28));

        address agentSigner = ecrecover(h, v, r, s);
        require (agentSigner != 0);
        require (agents[agentSigner] != 0);
        bytes32 check_h = keccak256(abi.encodePacked(_discount, msg.sender));
        require (check_h == h);

        uint remVal = ((20 - _discount)*msg.value)/100;
        totalCollected += msg.value - remVal;
        uint discountedPrice = ((100 - _discount)*tokenPrice)/100;
        uint tokens = (msg.value * 10**uint256(tokenContract.decimals())) / discountedPrice;

        require (tokenContract.transferFrom(spenderAddress, msg.sender, tokens));
        //Send the ether to the vault
        vaultAddress.transfer(msg.value - remVal);
        agents[agentSigner].transfer(remVal);

        return;
    }

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
