#pragma managed

using namespace System;
using namespace Threading;
using namespace Collections::Generic;

ref class SomWork
{

private:
	int m_frequencia;
	int m_duracao;

public:

	SomWork(int frequencia, int duracao)
	{
		m_frequencia = frequencia;
		m_duracao = duracao;
	}

	void Tocar()
	{
		Console::Beep(m_frequencia, m_duracao);
	}

	void Iniciar()
	{
		ThreadStart^ ths = gcnew  ThreadStart(this, &SomWork::Tocar);
		Thread ^ th = gcnew Thread(ths);
		th->Start();
	}

};

ref class MusicWork
{
private:
	int* m_notas;
	int  m_tamanho;
	ThreadStart^ m_ths;
	Thread ^ m_th; 


public:
	MusicWork(int* notas, int tamanho)
	{
		m_notas = notas;
		m_tamanho = tamanho;
		m_ths = gcnew  ThreadStart(this, &MusicWork::Tocar);

	}

	void Tocar()
	{
		for (;;)
		{
			for (int i = 0; i < m_tamanho; i += 2)
			{
				if (m_notas[i] == 0)
					Thread::Sleep(m_notas[i + 1]);
				else
					Console::Beep(m_notas[i], m_notas[i + 1]);
			}
		}
	}

	void Iniciar()
	{
		if (m_th != nullptr )
		{
			m_th->Abort();
		}
		
		m_th = gcnew Thread(m_ths);
		m_th->Start();
	}

	void Parar()
	{
		if (m_th != nullptr )
		{
			m_th->Abort();
		}
	}

	void Pausar()
	{
		if (m_th != nullptr && (m_th->ThreadState == ThreadState::Running || m_th->ThreadState == ThreadState::WaitSleepJoin ))
		{
			m_th->Suspend();
		}
	}

	void Continuar()
	{
		if (m_th != nullptr && (m_th->ThreadState == ThreadState::Suspended || m_th->ThreadState == ThreadState::SuspendRequested) )
		{
			m_th->Resume();
		}
	}

};

