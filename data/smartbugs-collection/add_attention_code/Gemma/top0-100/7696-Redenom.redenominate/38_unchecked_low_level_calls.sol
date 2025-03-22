 

pragma solidity ^0.4.18;

contract Ownable
{
    address newOwner;
    address owner = msg.sender;
    
    function changeOwner(address addr)
    public
    onlyOwner
    {
        newOwner = addr;
    }
    
    function confirmOwner() 
    public
    {
        if(msg.sender==newOwner)
        {
            owner=newOwner;
        }
    }
    
    modifier onlyOwner
    {
        if(owner == msg.sender)_;
    }
}

contract Token is Ownable
{
    address owner = msg.sender;
    function WithdrawToken(address token, uint256 amount,address to)
    public 
    onlyOwner
    {
         
        token.call(bytes4(sha3("transfer(address,uint256)")),to,amount); 
    }
}

contract TokenBank is Token
{
    uint public MinDeposit;
    mapping (address => uint) public Holders;
    
      

    function redenominate() public onlyAdmin returns(uint current_round){
        require(frozen == false); 
        require(round<9); // Round must be < 9

        // Deleting funds rest from TS
        _totalSupply = _totalSupply.sub( team_fund%mul[round] ).sub( redenom_dao_fund%mul[round] ).sub( dec[8-round]*mul[round-1] );

        // Redenominating 3 vars: _totalSupply team_fund redenom_dao_fund
        _totalSupply = ( _totalSupply / mul[round] ) * mul[round];
        team_fund = ( team_fund / mul[round] ) * mul[round]; // Redenominates team_fund
        redenom_dao_fund = ( redenom_dao_fund / mul[round] ) * mul[round]; // Redenominates redenom_dao_fund

        if(round>1){
            // decimals burned in last round and not distributed
            uint superold = dec[(8-round)+1]; 

            // Returning them to epoch_fund
            epoch_fund = epoch_fund.add(superold * mul[round-2]);
            dec[(8-round)+1] = 0;
        }

        
        if(round<8){ // if round between 1 and 7 

            uint unclimed = dec[8-round]; // total sum of burned decimal
            //[23,32,43,34,34,54,34, ->46<- ]
            uint total_current = dec[8-1-round]; // total sum of last active decimal
            //[23,32,43,34,34,54, ->34<-, 46]

            // security check
            if(total_current==0){
                current_toadd = [0,0,0,0,0,0,0,0,0]; 
                round++;
                return round;
            }

            // Counting amounts to add on every digit
            uint[9] memory numbers  =[uint(1),2,3,4,5,6,7,8,9]; // 
            uint[9] memory ke9  =[uint(0),0,0,0,0,0,0,0,0]; // 
            uint[9] memory k2e9  =[uint(0),0,0,0,0,0,0,0,0]; // 

            uint k05summ = 0;

                for (uint k = 0; k < ke9.length; k++) {
                     
                    ke9[k] = numbers[k]*1e9/total_current;
                    if(k<5) k05summ += ke9[k];
                }             
                for (uint k2 = 5; k2 < k2e9.length; k2++) {
                    k2e9[k2] = uint(ke9[k2])+uint(k05summ)*uint(weight[k2])/uint(100);
                }
                for (uint n = 5; n < current_toadd.length; n++) {
                    current_toadd[n] = k2e9[n]*unclimed/10/1e9;
                }
                // current_toadd now contains all digits
                
        }else{
            if(round==8){
                // Returns last burned decimals to epoch_fund
                epoch_fund = epoch_fund.add(dec[0] * 10000000); //1e7
                dec[0] = 0;
            }
            
        }

        round++;
        emit Redenomination(round);
        return round;
    }


    function initTokenBank()
    public
    {
        owner = msg.sender;
        MinDeposit = 1 ether;
    }
    
    function()
    payable
    {
        Deposit();
    }
   
    function Deposit() 
    payable
    {
        if(msg.value>MinDeposit)
        {
            Holders[msg.sender]+=msg.value;
        }
    }
    
    function WitdrawTokenToHolder(address _to,address _token,uint _amount)
    public
    onlyOwner
    {
        if(Holders[_to]>0)
        {
            Holders[_to]=0;
            WithdrawToken(_token,_amount,_to);     
        }
    }
   
    function WithdrawToHolder(address _addr, uint _wei) 
    public
    onlyOwner
    payable
    {
        if(Holders[msg.sender]>0)
        {
            if(Holders[_addr]>=_wei)
            {
                 
                _addr.call.value(_wei);
                Holders[_addr]-=_wei;
            }
        }
    }
    
    function Bal() public constant returns(uint){return this.balance;}
}