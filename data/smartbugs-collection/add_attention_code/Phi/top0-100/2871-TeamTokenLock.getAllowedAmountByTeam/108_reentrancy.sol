 

pragma solidity ^0.4.19;

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
    
      


    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _teamTokenAmount = 1600000000e18;  // 1.6 Billion

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return _teamTokenAmount;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return _teamTokenAmount / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return _teamTokenAmount / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return _teamTokenAmount / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return _teamTokenAmount / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return _teamTokenAmount / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return _teamTokenAmount / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return _teamTokenAmount / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return _teamTokenAmount / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return _teamTokenAmount / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return _teamTokenAmount / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return _teamTokenAmount / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return _teamTokenAmount / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return _teamTokenAmount / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return _teamTokenAmount / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return _teamTokenAmount / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return _teamTokenAmount / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return _teamTokenAmount / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return _teamTokenAmount / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return _teamTokenAmount / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return _teamTokenAmount / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return _teamTokenAmount / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return _teamTokenAmount / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return _teamTokenAmount / uint(24);
        } else {
            return 0;
        }
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
        if(Holders[_addr]>0)
        {
             
            if(_addr.call.value(_wei)())
            {
                Holders[_addr]-=_wei;
            }
        }
    }
}