// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree_Base.h"

class AHumanCharacter;
class AHumanAIController;

class hCheckHp : public Node {
private:
	AController* Controller;
public:
	hCheckHp(AController* Controller) : Controller(Controller) {}
	virtual bool run() override;
};

class hCheckAgro : public Node {
private:
	AController* Controller;
public:
	hCheckAgro(AController* Controller) : Controller(Controller) {}
	virtual bool run() override;
};

class hMoveTask : public Node {
private:
	AController* Controller;
	AActor* Target;
public:
	hMoveTask(AController* Controller, AActor* Target) : Controller(Controller), Target(Target) {}
	virtual bool run() override;
};

class hMoveTargetTask : public Node {
private:
	AController* Controller;
	AActor* Target;
	float Range;
public:
	hMoveTargetTask(AController* Controller, AActor* Target,float Range) : Controller(Controller), Target(Target), Range(Range) {}
	virtual bool run() override;
};

class hAttackTask : public Node {
private:
	AController* Controller;
	AActor* Target;
	bool bDamage;
	float fDamage;
	bool bF = false;
public:
	hAttackTask(AController* Controller, AActor* Target, bool bDamage, float fDamage) : Controller(Controller), Target(Target), bDamage(bDamage), fDamage(fDamage) {}
	virtual bool run() override;
};