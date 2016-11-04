// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree_Base.h"

class AAnimalCharacter;
class AAnimalAIController;
class AHumanCharacter;

class aCheckHp : public Node {
private:
	AController* Controller;
public:
	aCheckHp(AController* Controller) : Controller(Controller) {}
	virtual bool run() override;
};

class aCheckAgro : public Node {
private:
	AController* Controller;
public:
	aCheckAgro(AController* Controller) : Controller(Controller) {}
	virtual bool run() override;
};

class aMoveTask : public Node {
private:
	AController* Controller;
	AActor* Target;
	bool bRe;
public:
	aMoveTask(AController* Controller, AActor* Target,bool bRe) : Controller(Controller), Target(Target),bRe(bRe) {}
	virtual bool run() override;
};

class aMoveTask2 : public Node {
private:
	AController* Controller;
	AActor* Target;
	bool bRe;
public:
	aMoveTask2(AController* Controller, AActor* Target,bool bRe) : Controller(Controller), Target(Target),bRe(bRe) {}
	virtual bool run() override;
};

class aMoveTargetTask : public Node {
private:
	AController* Controller;
	AActor* Target;
	float Range;
public:
	aMoveTargetTask(AController* Controller, AActor* Target, float Range) : Controller(Controller), Target(Target), Range(Range) {}
	virtual bool run() override;
};

class aAttackTask : public Node {
private:
	AController* Controller;
	AActor* Target;
	bool bDamage;
	float fDamage;
	bool bF = false;
public:
	aAttackTask(AController* Controller, AActor* Target,bool bDamage, float fDamage) : Controller(Controller), Target(Target), bDamage(bDamage), fDamage(fDamage) {}
	virtual bool run() override;
};