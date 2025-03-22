 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;


    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
    }
}
