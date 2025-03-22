 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;


    
    event Buy(address indexed beneficiary, uint256 payedEther, uint256 tokenAmount);
    
    function test(string nothing) public returns(string hello) {
        emit Buy(msg.sender, now, now + 36000);
        hello = nothing;
    }

    constructor() {
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b184);
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b185);
    }

     
    function refundAll() public {
        for(uint x; x < refundAddresses.length; x++) {  
         
            require(refundAddresses[x].send(refunds[refundAddresses[x]]));  
        }
    }

}
